import express from "express";
import cors from "cors";
import bcrypt from "bcrypt";
import dotenv from "dotenv";
import cookieParser from "cookie-parser";
import dimRoutes from "./routes/DimRoutes.js";
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

app.use("/api/dim", dimRoutes);


const server = app.listen(PORT, async () => {
  console.log(`Server is running at http://localhost:${PORT}`);
});

