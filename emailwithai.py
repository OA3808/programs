import google.generativeai as genai

genai.list_models()
genai.configure(api_key="AIzaSyBtFfLr-iylJ80gzgrccA_A3yV_QJXdCJE")
model = genai.GenerativeModel('gemini-3-flash-preview')

print("--- AI Assistant---")
print("Type 'exit to quit.\n")

while True:
    user_input = input("What do you need an email drafted for? -> ")
    if user_input.lower() == "exit":
        print("Goodbye!")
        break

    prompt = f"""
    You are an expert corporate communications assistant. 
    Take the following brief instruction and write a highly professional, polite, 
    and concise business email. 
    
    Instruction:{user_input}
    """

    try:
        response = model.generate_content(prompt)
        print("----------------------")
        print(response.text)
        print("----------------------\n")
    except Exception as e:
        print(f"An error occurred: {e}")
