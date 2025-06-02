// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie jakiś czas temu...","Jeszcze nigdy nie spotkałem ludzi z taką ciekawością w mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moim zadaniem jest budować statki. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Umph, gdzież się podziała moja pamięć...","Hm, cóż...","Idź dalej...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... godny wybór, panie. Więc, czy to umowa?";
			link.l1 = " T-tak! Na zdrowie! Zawiń to i wyślij na molo. I pośpiesz się, dama czeka na mnie na ulicy!";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "Pięćdziesiąt tysięcy srebra za wszystko, panie.";
			if (sti(pchar.money) >= 55000) {
				link.l1 = "Il-ile powiedziałeś? Pi-pięćdziesiąt tysięcy? No, policz to sam! I weź jeszcze pięć tysięcy jako napiwek. Chodźmy!";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "Nie, nie, mogę być bogatym, hic! ...gościem, ale za tyle tego nie wezmę. Nie, panie! Żegnaj, łodziarzu.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "Dziękuję, panie. Niech ci dobrze służy!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "Tak, spadaj, bogaczu. Zamknęliśmy trzy godziny temu.";
			link.l1 = " ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
