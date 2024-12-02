import axios from "axios";
import { db } from "../config/firebaseConfig.js";

export const getDis = async (request, response, next) => {
	try {
		const docRef = db.collection("distance").doc("001");
		const doc = await docRef.get();

		console.log("heloo");

		if (!doc.exists) {
			return response.status(404).json({ message: "data not found" });
		}

		const docData = await doc.data();
		console.log(docData);

		const baseUrl = docData.url;
		const res = await axios.get(baseUrl, {
			headers: { "Content-Type": "application/json" },
		});

		console.log(res.data);

		const responseData = res.data;
		console.log(responseData);

		await docRef.set(
			{
				dis: responseData.dis,
			},
			{ merge: true }
		);

		return response
			.status(200)
			.json({ data: { dis: responseData.dis }, message: "success" });
	} catch (error) {
		console.error(error);
		return response.status(500).json({ message: "Error fetching data" });
	}
};
