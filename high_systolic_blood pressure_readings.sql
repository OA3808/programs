DROP TABLE IF EXISTS Observations;
DROP TABLE IF EXISTS Encounters;
DROP TABLE IF EXISTS Providers;
DROP TABLE IF EXISTS Patients;

CREATE TABLE Patients (
    PatientID INTEGER PRIMARY KEY,
    FirstName TEXT NOT NULL,
    LastName TEXT NOT NULL,
    BirthDate TEXT,
    Gender TEXT,
    City TEXT
);

CREATE TABLE Providers (
    ProviderID INTEGER PRIMARY KEY,
    FullName TEXT NOT NULL,
    Specialty TEXT
);

CREATE TABLE Encounters (
    EncounterID INTEGER PRIMARY KEY,
    PatientID INTEGER,
    ProviderID INTEGER,
    VisitDate TEXT,
    Department TEXT,
    FOREIGN KEY (PatientID) REFERENCES Patients(PatientID),
    FOREIGN KEY (ProviderID) REFERENCES Providers(ProviderID)
);

CREATE TABLE Observations (
    ObservationID INTEGER PRIMARY KEY,
    EncounterID INTEGER,
    ObsType TEXT,
    Value REAL,
    Unit TEXT,
    FOREIGN KEY (EncounterID) REFERENCES Encounters(EncounterID)
);

INSERT INTO Patients (PatientID, FirstName, LastName, BirthDate, Gender, City) VALUES (1, 'Jane', 'Smith', '1985-10-12', 'Female', 'Toronto');
INSERT INTO Patients (PatientID, FirstName, LastName, BirthDate, Gender, City) VALUES (2, 'Robert', 'Miller', '1955-03-24', 'Male', 'Ottawa');

INSERT INTO Providers (ProviderID, FullName, Specialty) VALUES (101, 'Dr. Alice Wong', 'Cardiology');
INSERT INTO Providers (ProviderID, FullName, Specialty) VALUES (102, 'Dr. Sam Patel', 'Family Medicine');

INSERT INTO Encounters (EncounterID, PatientID, ProviderID, VisitDate, Department) VALUES (5001, 1, 101, '2026-04-01', 'Cardiology');
INSERT INTO Encounters (EncounterID, PatientID, ProviderID, VisitDate, Department) VALUES (5002, 1, 102, '2026-04-15', 'Emergency');
INSERT INTO Encounters (EncounterID, PatientID, ProviderID, VisitDate, Department) VALUES (5003, 2, 102, '2026-04-20', 'Family Medicine');

-- Mock vitals for Jane Smith (High Blood Pressure case)
INSERT INTO Observations (ObservationID, EncounterID, ObsType, Value, Unit) VALUES (1, 5001, 'Systolic BP', 145, 'mmHg');
INSERT INTO Observations (ObservationID, EncounterID, ObsType, Value, Unit) VALUES (2, 5002, 'Systolic BP', 152, 'mmHg');
-- Normal Heart Rate for Robert
INSERT INTO Observations (ObservationID, EncounterID, ObsType, Value, Unit) VALUES (3, 5003, 'Heart Rate', 72, 'bpm');

SELECT p.FirstName, p.LastName, COUNT(o.ObservationID) AS HighBPCount
FROM Patients p 
JOIN Encounters e ON p.PatientID = e.PatientID
JOIN Observations o ON e.EncounterID = o.EncounterID
WHERE o.ObsType = 'Systolic BP' AND o.Value > 140
GROUP BY p.PatientID, p.FirstName, p.LastName
HAVING COUNT(o.ObservationID) > 1;
