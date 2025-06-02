// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"...","Po raz trzeci dzisiaj mówisz o jakimś pytaniu...","Patrz, jeśli nie masz nic do powiedzenia o sprawach portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Czy imię 'Juan' coś ci mówi?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Señor, w kwietniu 1654 roku był tu fregata pod dowództwem Miguela Dichoso. Potem zniknął. Czy niczego sobie nie przypominasz o tym? Być może Dichoso był tutaj i zarejestrował swój statek...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Juan? To wszystko? Senor, czy jesteś pijany, czy stroisz sobie ze mnie żarty? Czy możesz przypomnieć sobie nazwisko lub przynajmniej nazwę jego statku? To hiszpańska kolonia, na Boga. Wiesz, ilu mamy tu Juanów? Nie będę w stanie ci pomóc bez żadnych szczegółów.";
			link.l1 = "Rozumiem. Przepraszam za kłopot...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Zobaczmy moje notatki... aha! Tak, kapitan Miguel Dichoso był tutaj w kwietniu 1654 roku, na fregacie 'Santa-Quiteria'. Zarejestrował się jako przybywający z kolonii San-Andres, Providence. Zmierzał do Kadyksu, Hiszpania. Odpłynął 14 kwietnia 1654 roku. To wszystko, co mam.";
			link.l1 = "Żeglujesz do Europy? Rozumiem. Dzięki za to!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
