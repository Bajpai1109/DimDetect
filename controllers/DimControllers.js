import { db } from "../config/firebaseConfig.js";

// import axios from "axios";

// export const getDis = async (request, response, next) => {
//     try {
//         // Perform a GET request to the provided URL
//         console.log("hello");
        
//         const url = "https://10e8-106-222-212-219.ngrok-free.app";
//         const apiResponse = await axios.get(url);

//         // Log and return the response from the external API
//         console.log(apiResponse.data);
//         return response.status(200).json(apiResponse.data);

//     } catch (error) {
//         console.error("Error fetching data from external URL:", error.message);
//         return response.status(500).json({ message: "Error fetching data from external URL" });
//     }
// };

import axios from "axios";
import https from "https";

export const getDis = async (request, response, next) => {
    try {
      console.log("Attempting to fetch data from external URL...");
  
      const url = "https://10e8-106-222-212-219.ngrok-free.app";
  
      // Configure axios to ignore HTTPS certificate issues during development
      const httpsAgent = new https.Agent({ rejectUnauthorized: false });
  
      // Perform the GET request to the external API
      const apiResponse = await axios.get(url, { httpsAgent });
  
      // Log and return the response from the external API
      console.log("Response from external API:", apiResponse.data);
      return response.status(200).json(apiResponse.data);
  
    } catch (error) {
      // Log detailed error information for debugging
      console.error("Error fetching data from external URL:", error.message);
  
      if (error.response) {
        console.error("Error response data:", error.response.data);
        console.error("Error response status:", error.response.status);
      }
  
      // Send a meaningful error response
      return response.status(500).json({ message: "Error fetching data from external URL" });
    }
  };