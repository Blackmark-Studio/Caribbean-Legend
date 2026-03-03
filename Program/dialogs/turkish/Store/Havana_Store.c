// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Tam da bundan bahsediyorduk. Herhalde unuttunuz...","Bugün üçüncü kez bir şey soruyorsun...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unutmuşum...","Evet, gerçekten de üçüncü kez...","Hm, yapamam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Dinle, Joachim Merriman adında bir adam hiç buraya, dükkanına geldi mi? Orta yaşlı bir bey, Portekizli, bıyıklı, keçi sakallı ve delici bakışlı? Belki bir şey satın almıştır?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Hayır, müşterilerim arasında tarif ettiğiniz kişiye benzeyen biri yok. Ayrıca, o ismi de daha önce hiç duymadım. Üzgünüm, size daha fazla yardımcı olamam.";
			link.l1 = "Anladım. Yazık. Neyse, aramaya devam edeceğim...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
