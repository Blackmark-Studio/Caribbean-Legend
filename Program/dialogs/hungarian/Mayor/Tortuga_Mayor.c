// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek, mi a kérdés?"), "Ez már a második alkalom, hogy megpróbálsz kérdezni...", "Ez a harmadik alkalom, hogy megpróbálod megkérdezni...",
                          "Mikor lesz ennek vége?! Elfoglalt ember vagyok, gyarmati ügyekkel foglalkozom, és te még mindig zaklatsz!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, sajnálom.", "Ne most. Rossz helyen és rossz idôben."), "Igaz, most nincs mit mondanom, sajnálom.",
                      "Majd késôbb megkérdezem.", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Kormányzó úr, szörnyû híreim vannak az ön számára. Rövid leszek: a felesége ki akarja rabolni önt. Megpróbált rávenni, hogy feltörjem az egyik szekrényét. Gondoltam, tudnia kell errôl.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", ...Monsieur. Chevalier de Poincy fôkormányzó parancsára vagyok itt. Az a feladatom, hogy Tortugára szállítsak egy Noel Forget nevû bárót, aki az anyaállamból érkezett azzal a paranccsal, hogy ellenôrizze a kolóniákat. Fô célja egy francia nyugat-indiai kereskedelmi társaság létrehozása. Hadd mutassam be önnek... Minden részletet ô maga fog elmagyarázni.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "Mi-mi-mi? Már megint? Az a kurva! Meg fogja ezt bánni, esküszöm! Kampacho sikoltozni fog. Miért vagy még mindig itt? Takarodj innen a pokolba!";
			link.l1 = "Azt hittem...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Mindig ugyanaz! Tessék, fogd ezt! Ez minden, ami az asztalon van! Most pedig kifelé!";
			link.l1 = "Köszönöm, excellenciás uram. Kikísérem magam.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("Kaptál egy duplacsövû pisztolyt és egy erszényt tele dublonnal.");
			dialog.text = "Mindig ugyanaz! Tessék, fogd ezt! Ez minden, ami az asztalon van!... Bár, rendben, nem úgy nézel ki, mint a többi idióta és lúzer, akikkel tele van a szigetem. Vegyél még egy kicsit... Most pedig kifelé!";
			link.l1 = "Köszönöm, excellenciás uram. Kikísérem magam.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "Rendben, Charles de Maure kapitány. A bárónak megfelelô bánásmódban lesz része, és én mindent megteszek, hogy segítsek neki a feladatában.";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
