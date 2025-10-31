// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Úgy értesültem, hogy járvány van itt, igazam van?";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Igazad van, úgyhogy komoly ok nélkül ne látogassátok a tömlöcöket. Miért érdekel ez téged?";
			link.l1 = "Csak kíváncsiságból. Tehát ha a fiaim túlságosan berúgnak, túl nagy zajt csapnak, és itt kötnek ki, akkor készítsek elô néhány sárga vásznat?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Sajnos, rangidôs, nem értem a viccet, ha esetleg vicceltél volna. A várbörtönök nedvesek és hidegek, és te ismered az éghajlatot. A fogyasztás gyakori vendég ezekben a tömlöcökben. Még a legényeimnek is fizetnem kell, hogy ételt hozzanak a kamrákba. Az ottani ôrjáratozás egyenlô a büntetômunkával.";
			link.l1 = "Elnézést, csak azt akartam tudni, hogy ez mennyire komoly dolog?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Túlságosan is komoly. Itt még orvosunk sincs, ô is belehalt abba a rohadt fogyasztásba. Most már csak a helyi helyôrség orvosa vizsgálja meg a foglyokat hetente egyszer. De kit érdekelnek ezek a csavargók és bûnözôk?\nA legtöbb ember úgy gondolja, hogy teljesen megérdemelték ezt a sorsot, és ezzel nehéz vitatkozni.";
			link.l1 = "Az orvosi ismereteim szerények, de amennyire tudom, a fogyasztás veszélyes és halálos, de nem öli meg az embereket néhány nap alatt, mint itt. Nem kellene az áldozatoknak hónapokig vagy akár évekig szenvedniük?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Ahogy az imént említetted, nem vagy orvos, ezért a betegség jellemzôirôl beszélni csak... kitalált hazugság lehet. Én csak megismételtem, amit az orvosunk mondott, mielôtt a betegség ôt is elvitte. Szóval nem értem a kíváncsiságodat és a cinikus viselkedésedet. Itt emberek halnak meg!";
			link.l1 = "Nem azt mondtad, hogy megérdemlik?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Elég, idôsebb! Azt hiszem, hogy neked és nekem más dolgunk is van, mint az okoskodásban való versengés. Az ajtó ott van mögötted.";
			link.l1 = "Rendben, bocsássátok meg tapintatlanságomat, máris megyek.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
