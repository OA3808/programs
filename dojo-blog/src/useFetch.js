import {useState, useEffect} from 

const useFetch = () => {
    const [blogs, setBlogs] = useState(null);
    const [isPending, setIsPending] = useState(true);
    const [error, setError] = useState(null)
    
    useEffect(() => {
            setTimeout(() => {
                fetch("http://localhost:8000/blogs")
                .then(res => {
                    console.log(res);
                    if(!res.ok) {
                        throw Error('could not fetch the data for that reaource');
                    }
                    return res.json();
                })
                .then(data => {
                    setBlogs(data);
                    setIsPending(false);
                    setError(null);
                })
                .catch(err => {
                    setIsPending(false);
                    setError(err.message);
                })
            console.log("use effect ran");
            console.log(blogs);
            }, 1000);
        }, []);
}