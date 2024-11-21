import { db } from "../config/firebaseConfig.js";


export const getDis = async (request, response, next) => {
    try {
        const docRef = db.collection("distance").doc("001");
        const doc = await docRef.get();

        if(!doc.exists){
            return response.status(404).json({ message: "data not found" });
        }

        const docData = await doc.data();
        console.log(docData);
        return response.status(200).json({docData});
    } catch (error){
        console.error(error);
        return response.status(500).json({ message: "Error fetching data" });
    }
}