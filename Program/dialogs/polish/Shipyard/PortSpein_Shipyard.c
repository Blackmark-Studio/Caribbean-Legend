// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie przed chwilą...","Nie spotkałem ludzi z taką ciekawością w mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moja praca polega na budowaniu statków. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam nic do omówienia w tej chwili."),"Umph, gdzież to moja pamięć się podziała...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Czy imię Juan coś ci mówi?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Señor, w kwietniu 1654 roku była tu fregata pod dowództwem Miguela Dichoso. Zniknęła zaraz potem. Czy nie pamiętasz niczego na ten temat? Może Dichoso zatrzymał się na naprawę, a może coś ci powiedział...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Nie. Nic a nic.";
			link.l1 = "Dobrze. Przepraszam, że przeszkadzam...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. Nie. Nie zatrzymał się na naprawę i nic mi nie powiedział. A jeśli cokolwiek z tego się wydarzyło, to nie mogę sobie tego przypomnieć. Przykro mi, że nie mogę ci pomóc, señor.";
			link.l1 = "W porządku. Gracias amigo...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
