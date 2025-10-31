// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "Tiszt úr, van itt egy foglya, Bartolomeo, a portugál...";
                link.l1.go = "Portugal";
            }
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Igen, így van. És miért érdekli ez magukat? Csak a Holland Nyugat-indiai Társaság követei láthatják ôt, és csak a kormányzó írásos parancsára. A Társaság egyik tisztje éppen most hallgatja ki ezt a kalózt. Szóval ha csak azért jöttek ide, hogy lássák, akkor jobb, ha elmennek, látni fogják, amikor felakasztják, most menjenek el.";
			link.l1 = "Nem azért jöttem ide, hogy lássam ôt.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Akkor miért, ha megkérdezhetem?";
			link.l1 = "Azért jöttem ide... hogy kiszabadítsam ôt!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
