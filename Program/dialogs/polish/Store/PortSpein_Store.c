// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Śmiało, czego chcesz?"," Właśnie o tym rozmawialiśmy. Musisz mieć sklerozę...","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Słuchaj, to jest sklep. Ludzie tu kupują rzeczy. Nie przeszkadzaj mi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Racja, zapomniałem z jakiegoś powodu...","Tak, to naprawdę już trzeci raz...","Hm, nie będę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Czy imię Juan coś ci mówi?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "W kwietniu 1654 roku fregata zacumowała w waszym porcie pod dowództwem kapitana Miguela Dichoso, po czym zniknął. Czy jego imię coś ci mówi? Może kupił od ciebie jakieś towary lub coś powiedział...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Oj, daj spokój, kapitanie! Dzisiaj miałem dwóch Juanów w moim sklepie, a wczoraj jeszcze jednego. Co, mam pamiętać każdego z nich?";
			link.l1 = "Dobrze. Przepraszam, że zawracam ci głowę...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "O, kapitanie, przez ten czas przewinęło się tu tyle fregat i galeonów, Miguele i Carlosie...";
			link.l1 = "Rozumiem. Czyli nie możesz mi pomóc...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
