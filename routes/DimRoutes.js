import { Router } from "express";
import { getDis } from "../controllers/DImControllers.js";

const dimRoutes = Router();

dimRoutes.get("/distance", getDis);

export default dimRoutes;
