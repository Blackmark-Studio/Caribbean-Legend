void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nie mamy o czym rozmawiać!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Cześć! Nazywam się  "+GetFullName(npchar)+". Co mogę dla ciebie zrobić?","Witaj ponownie!","Goście są bardzo rzadkością w tych zapadłych zakątkach...","To taka przyjemność rozmawiać z nową twarzą! Już mi się przejadły te stare ryje...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("O, nic...","Ja też...","Widzę...","Heh...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Zbieramy tu perły, służymy  "+NationNameGenitive(sti(npchar.nation))+", wiesz...";
			link.l1 = "Tak, wiem...";
			link.l1.go = "exit";
			link.l2 = "Hej, posłuchaj, czy można kupić kilka tych drobiazgów bezpośrednio od 'producenta', co byś powiedział?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "O nie, oczywiście, że nie! Kradzież nawet jednej małej perły jest karana śmiercią!";
				link.l1 = "Okrutne rozkazy macie tutaj, na pewno...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Tak, mamy tu surowe rozkazy, i jeden może łatwo stracić swoją głowę za wszelkie występki. Ja w to nie wchodzę, ale mogę ci doradzić, abyś porozmawiał z miejscowymi Indianami na ten temat. Oni mają gdzie uciec, jeśli coś pójdzie nie tak, więc powinni być odważniejsi niż my...";
				link.l1 = "Rozumiem... Dobrze, dzięki.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Czy ty "+GetSexPhrase("zwariowałeś? Spadaj, idioto","zwariowałaś? Spadaj, latawico")+"!",""+GetSexPhrase("Co?! Czy ty oszalałeś, idioto","Co?! Postradałaś zmysły, głupia dziewczyno")+"?! Zabieraj się ze wszystkimi swoimi pytaniami...",""+GetSexPhrase("Straciłeś rozum, drogi? Jacy piraci? Tutaj?! Spływaj stąd, palancie","Czy straciłaś rozum, kochanie? Jacy piraci? Tutaj?! Spływaj stąd, głupia dziewczyno")+"...");
			link.l1 = RandPhraseSimple("Nie ma potrzeby być niegrzecznym...","Zważaj na swe słowa!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Bladatwarz","Bladatwarz")+" chce rozmawiać?","Ty znowu, "+GetSexPhrase("bladatwarz","bladatwarz")+".",""+GetSexPhrase("Blady lubi rozmawiać. Wygląda jak kobieta.","Blada lubi rozmawiać.")+"","Duchy przyprowadziły mi "+GetSexPhrase("bladego brata"," bladą siostre")+" do mnie.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tak.","Tak, to znowu ja.","Bardzo poetycko.","Cieszę się również, że cię widzę",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Powiedz mi, dlaczego tu przyszedłeś.";
			link.l1 = "Oh, nic konkretnego, po prostu chciałem posłuchać, co masz do powiedzenia.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Kapitanie, co robisz? Schowaj swoją broń, zanim narobisz dużo kłopotów!";
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Nie martw się, już to odkładam...");
			link.l1.go = "exit";
		break;  

	}
}
