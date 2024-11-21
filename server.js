import express from "express";
import cors from "cors";
import bcrypt from "bcrypt";
import dotenv from "dotenv";
import cookieParser from "cookie-parser";
import dimRoutes from "./routes/DimRoutes.js";
import axios from "axios";
// import admin from "./config/firebaseConfig.js";

dotenv.config();

const app = express();
const PORT = process.env.PORT || 3001;
const databaseUrl = process.env.DATABASE_URL;

app.use(
  cors({
    origin: process.env.ORIGIN,
    methods: ["GET", "POST", "PUT", "PATCH", "DELETE"],
    credentials: true,
  })
);

app.use(cookieParser());
app.use(express.json());

// app.use("/api/dim", dimRoutes);

app.get('/api/dim/distance', async (req, res) => {
  try {
      // External API URL (ngrok URL)
      const url = "https://10e8-106-222-212-219.ngrok-free.app";
      console.log("Attempting to fetch data from external URL...");

      // Make the GET request to the external API
      const apiResponse = await axios.get(url);

      // Log and return the response from the external API
      console.log(apiResponse.data);
      return res.status(200).json(apiResponse.data); // Send the response data to the client

  } catch (error) {
      console.error("Error fetching data from external URL:", error.message);
      if (error.response) {
          // If the server responded with an error
          console.error("Response data:", error.response.data);
          console.error("Response status:", error.response.status);
      } else if (error.request) {
          // If no response was received
          console.error("Request data:", error.request);
      }
      return res.status(500).json({ message: "Error fetching data from external URL" });
  }
});

// app.listen(port, () => {
//   console.log(`Server is running at http://localhost:${port}`);
// });

const server = app.listen(PORT, async () => {
  console.log(`Server is running at http://localhost:${PORT}`);
});

