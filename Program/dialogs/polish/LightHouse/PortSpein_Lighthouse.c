// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz?","Czego chciałbyś się dowiedzieć?"),"Czego ci potrzeba, "+GetAddress_Form(NPChar)+"?","To już trzeci raz, gdy próbujesz mnie zapytać...","Mam cię dość, zmykaj!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Przepraszam, zmieniłem zdanie.","To nic, przepraszam."),"Zapomniałem, przepraszam...","Do trzech razy sztuka, co? Przepraszam...","Przepraszam, przepraszam! Już się wynosze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Słuchaj, fregata pod dowództwem Miguela Dichoso była tutaj w kwietniu 1654 roku, potem zniknęła. Czy możesz mi powiedzieć więcej o jego statku? Może widziałeś, co się z nim stało lub dokąd popłynął? Czy coś pamiętasz?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Aye, Señor, to był widok, który zapierał dech w piersiach! Takich rzeczy się nie zapomina, ha!";
			link.l1 = "Czy możesz mi powiedzieć, co się stało?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Fregata Seniora Dichoso zarzuciła kotwicę w porcie San Jose. Miałem świetny widok, by wszystko zobaczyć, owszem. Powiem ci, to była doskonała fregata, arcydzieło, przysięgam na moje krwawiące serce! Załoga chwaliła się szybkością, mogła osiągnąć szesnaście węzłów! Spędzili tu dzień, a potem wyruszyli prosto na wyspę Tobago. Następnie, nie uwierzysz, zaczęły się dziać dziwne rzeczy z pogodą, jak tylko zniknęli za horyzontem. Pogoda była świetna przez wiele dni, ani jednej chmurki! A jednak ta straszna burza pojawiła się znikąd. Wyglądało to tak, jakby sam Neptun nas odwiedził! Wszedłem na szczyt mojego latarni, by ją zapalić, ale wtedy ją zobaczyłem... Santa Quiteria! Pędziła na olbrzymich falach w towarzystwie gigantycznego tornada! Fregata przeleciała obok mojej latarni jak iskra, a potem burza poprowadziła ją na północny zachód! Od tego czasu nikt nie widział Santa Quiteria. Zaledwie godzinę później wiatr, deszcz i chmury zniknęły, a słońce świeciło, ani śladu burzy! Nigdy czegoś takiego nie widziałem! Chociaż tego dnia zebrałem z mojej zatoki tyle bursztynu...";
			link.l1 = "Więc burza zepchnęła fregatę z powrotem na Morze Karaibskie?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Tak jest! Daleko za horyzontem na Martynikę. Wątpię, by Dichoso mógł przetrwać tę burzę, choć robił co mógł! Fregata nie tonęła, ale Santa Quiteria musi już leżeć na dnie morza pośród koralowców... Właściwie, nie jesteś pierwszą osobą, która pyta mnie o Dichoso i jego fregatę.";
			link.l1 = "Naprawdę? Kto jeszcze interesował się Miguelem?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Jakiś śmiały kapitan hiszpańskiej floty, nie mniej! Przedstawił się jako... och... zapomniałem... Ach! Señor Diego. Nazywał się Diego, ale nazwisko... de Montagna albo de Montoya. Coś w tym stylu. Słuchał mnie tak jak ty teraz, podziękował i odszedł. Od tamtej pory go nie widziałem.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "Widzę. Dziękuję bardzo za twoją opowieść, bardzo mi pomogłeś. Przyjmij moją wdzięczność w monetach. Żegnaj.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "Rozumiem. Bardzo dziękuję za twoją opowieść, bardzo mi pomogłeś. Żegnaj.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
