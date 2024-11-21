import { Router } from "express";
import { getDis } from "../controllers/DimControllers.js";

const dimRoutes = Router();

dimRoutes.get("/distance", getDis);

export default dimRoutes;
