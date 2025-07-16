// Абрахам Норман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czy czegoś potrzebujesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Czego potrzebujesz, kumplu? Idź swoją drogą, zajmij się swoimi sprawami. Po prostu zostaw mnie w spokoju.","Hej, hej, kumplu. Wybierasz się na spacer? Cóż, po prostu idź dalej i zostaw pana Abrahama w spokoju. On też wybiera się na spacer. Zaczerpuje świeżego morskiego powietrza.","„Witaj, przyjacielu. Chcesz pogadać? Jest tylko jeden problem: nie mam nastroju na rozmowę. Więc poszukaj kogoś innego do zaczepienia. Idź się zrelaksować w tawernie. Napij się rumu...”");
				link.l1 = "Słuchaj, Abrahamie, czy przypadkiem nie natknąłeś się ostatnio na człowieka o imieniu Miguel Dichoso na Isla Tesoro? Jest tu dość znaną postacią.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Czego potrzebujesz, kumplu? Idź swoją drogą, zajmij się swoimi sprawami. Po prostu zostaw mnie w spokoju.","Hej, hej, kumplu. Wybierasz się na spacer? Cóż, po prostu idź dalej i zostaw pana Abrahama w spokoju. On też idzie na spacer. Łapie świeże morskie powietrze.","Cześć, kumplu. Chcesz pogadać? Jest tylko jeden problem: nie mam ochoty na rozmowy. Więc idź kogoś innego zaczepić. Idź odprężyć się w tawernie. Napij się rumu..."),LinkRandPhrase("Hej, Żeglarzu. Co, jesteś twardogłowy czy coś? Myślałem, że byłem dość jasny.","Przyjacielu, idź odpocząć. Wydajesz się trochę przygłuchy.","Hej kumplu, co, jesteś głupi czy coś? Już ci to praktycznie wyłożyłem."),"Chłopie, nie denerwuj mnie. Zatłukłem w swoim życiu tylu szczurów lądowych, że jeden więcej czy mniej naprawdę nie robi różnicy.","Dobrze, wkurzyłeś mnie. Teraz albo wyciągaj swój zardzewiały miecz, albo uciekaj, ile sił w nogach. Polecam drugą opcję...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("W porządku, przyjacielu. Nie będę cię niepokoić.","Dobrze, dobrze. Zrozumiałem...","O rany, wyglądasz jakbyś był gromem mórz! Dobra, zmywam się stąd.","Co?!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Czego potrzebujesz, kamracie? Idź swoją drogą, zajmij się swoimi sprawami. Po prostu zostaw mnie w spokoju.","Hej, hej, kumplu. Wybierasz się na spacer? Cóż, ty sobie spaceruj dalej i zostaw pana Abrahama w spokoju. On też idzie na spacer. Łapie oddech świeżego morskiego powietrza.","Cześć, koleżko. Chcesz pogadać? Jest tylko jeden problem: nie mam nastroju do rozmów. Więc idź niepokoić kogoś innego. Odpręż się w tawernie. Napij się rumu...");
				link.l1 = "Słuchaj, Abrahamie, czy przypadkiem nie natknąłeś się ostatnio na człowieka o imieniu Miguel Dichoso na Isla Tesoro? Jest tu dość znaną osobistością.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "Stój! Jestem gubernatorem tej wyspy. Co, nie wierzysz mi?!";
					link.l1 = "Oczywiście, że znam! Kto nie zna gubernatora Isla Tesoro...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ha, nazwij się admirałem, skoro przy tym jesteś, na pewno to kupię!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Na baczność! Oto - admirał Barbarigo! Nie rozpoznajesz mojego słynnego kawaleryjskiego miecza?";
					link.l1 = "Moje przeprosiny, Panie Admirale! Od teraz będę bardziej uważny.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "Twoja szabla kawaleryjska jest powszechnie znana. Szkoda tylko, że jest w rękach głupca.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "Jak widzisz, jestem tutaj na wygnaniu. Oczekuję dalszych wiadomości od generała Monka. Proszę cię, abyś nie rozgłaszał mojej ukrytej królewskiej tożsamości. Wywiad Cromwella ma długie uszy.";
					link.l1 = "Oczywiście, Wasza Wysokość. Nikt nigdy się nie dowie, że Karol II ukrywa się w Indiach Zachodnich.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "Cóż, w takim razie ja jestem papieżem Innocentym X.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "Co się z tobą stało, Blaze? Szukałem cię przez dwa dni. Całkowicie zapomniałeś o swoim ojcu Nicolasie!";
					link.l1 = "Nie mam czasu dla ciebie, ojcze! Jestem zawalony robotą.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "Pan się myli, sir. Nazywam się "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "S-sz... Jestem Davy Jones. Powiedz mi, boisz się śmierci?";
					link.l1 = "Oczywiście, że tak, panie Jones. Zwłaszcza po kacu.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "Jedna śmierć to tragedia, tysiąc śmierci to tylko statystyka.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "Spieszę się, by skończyć moją nową sztukę. Musisz mi pomóc dokończyć frazę 'Być albo nie być'?!";
					link.l1 = "To jest pytanie! Czy zniosimy tę zniewagę i ruszymy dalej...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "Napitek, na pewno. Ale nie zdziwię się, jeśli złapię chorobę w burdelu!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "Co do diabła mówisz? 'Tesoro'?! Możesz równie dobrze nazwać to Bermudami! Ta wyspa nazywa się Norman Island na moją cześć i nie zapomnij tego! Będę musiał nauczyć cię geografii...";
			link.l1 = "Cóż?! Co masz na myśli?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "Masz rację, Żeglarzu. W rzeczy samej, jestem admirałem Barbarigo, ale to między nami. Szykuj się do marszu. Wkrótce ruszamy. To ci się przyda.";
			link.l1 = "Jestem niezmiernie wdzięczny!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "Zaraz zobaczymy, kto tu jest głupcem. Na gardę!";
			link.l1 = "Naprawdę?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "A co ci mówiłem! Napij się za moje zdrowie.";
			link.l1 = "W zdrowie, admirale!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "Prosiłem cię, żebyś nie rozpowszechniał mojego imienia! Teraz będę musiał cię unieszkodliwić jako niebezpiecznego świadka...";
			link.l1 = "O, czekałem na to!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Przebacz mi, Wasza Łaskawość! Nie poznałem Cię w tym stroju. Proszę, przyjmij ten skromny dar od prawdziwego katolika.";
			link.l1 = "Szaleństwo się odzywa...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Wszyscy się na mnie rzucają! Złapałem szpiega, który wygląda dokładnie jak mój syn! Jestem pewien, że Thomas go przysłał, żeby wybić mi drugie oko!";
			link.l1 = "Odpieprz się, idioto!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "Jesteś zmęczony i nie wyglądasz za dobrze, młodzieńcze. Idź i poddaj się leczeniu.";
			link.l1 = "Dzięki!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "Nie bój się, kumplu. Widzisz, umieranie wcale nie jest straszne...";
			link.l1 = "Wygląda na to, że nie żartujesz!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "Najwyraźniej się nie boisz. Wiedziałem to. To jest odwaga!";
			link.l1 = "Jesteś zabawnym starym człowiekiem...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "Jesteś kiepskim poetą, Żeglarzu. Może twój miecz jest bardziej zręczny niż twój język?";
			link.l1 = "Caramba! Ten twój kawaleryjski miecz to wcale nie jest atrapa!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "Do diabła! Wszystko idzie dla ciebie jak po maśle! Co powiesz na to dla swojej wyobraźni!";
			link.l1 = "Przyjdź ponownie.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Aha, rozpoznaję cię! Ha-ha!";
			link.l1 = "Znowu...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "Dobrze, kumplu, pogadaliśmy sobie. Teraz ruszaj w drogę.";
			link.l1 = "Jak mówisz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso? Po co ci on, co?";
			link.l1 = "Cóż, potrzebuję go. Po prostu go potrzebuję. Więc widziałeś go?";
			link.l1.go = "tieyasal_1";
			link.l2 = "Co masz na myśli, co mi po nim? Miguel to mój stary druh, można rzec przyjaciel. On ma...";
			link.l2.go = "tieyasal_2";
			link.l3 = "Chcę, żeby przyholował dla mnie nową łajbę, tak jak to kiedyś zrobił dla Rekina Dodsona.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso zabił człowieka. Dlatego go szukam.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ty tylko jego potrzebujesz... Ty jeeego tylko potrzebujesz! Wszystko, czego ci trzeba, to Miguel Dichoso! Nie, nie widziałem go. Nie widziałem go od dawna. Nie mogę ci w niczym pomóc, Żeglarzu.";
			link.l1 = "Hm... No cóż, żegnaj.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "Przyjaciela, powiadasz... Wydaje się, że wyhodował sobie całą górę przyjaciół. Zaraz będzie miał o jednego mniej...";
			link.l1 = "Hej, staruszku. Co z tobą nie tak?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Tak, Dichoso jest mistrzem w takich rzemiosłach, jakkolwiek na to spojrzysz. Ale nie wiem, gdzie on jest. Przyszedł, ale znów się ulotnił. Więc idź do Alexusa, Żeglarzu. Zbuduje dla ciebie wspaniałą łajbę.";
			link.l1 = "Hm... Dzięki za wskazówkę, kumplu.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "A któż to taki, którego Dichoso za ciebie wytropił, że teraz go szukasz, co, kamracie? ";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_4_1":
			dialog.text = "Co masz na myśli? Którego dokładnie Sharp'a zabił? Wiesz, jest ich sporo.";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			sTemp = GetStrSmallRegister(dialogEditStrings[8]);
			if (sTemp == "blaze sharp")
			{
				dialog.text = "S-s-s...(rozglądając się) Więc ty też myślisz, że Blaze Sharp został zabity przez Dichoso?";
				link.l1 = "Tak. Mam nie tylko swoje podejrzenia, ale i solidne dowody. Wpisy w jego dzienniku pokładowym...";
				link.l1.go = "tieyasal_6";
				break;
			}
			if (sTemp == "sharp")
			{
				dialog.text = "Idź dalej, mały Żeglarzu...";
				link.l1 = "Co masz na myśli? Opowiedz mi więcej.";
				link.l1.go = "tieyasal_4_1";
				break;
			}
			dialog.text = "Ah...Cóż. Zabił go i tyle w temacie. Wiesz, ilu morderców tutaj się kręci? Co drugi człowiek! Nie, Żeglarzu. Nie widziałem Dichoso od dłuższego czasu. Nie mogę ci w niczym pomóc.";
			link.l1 = "Szkoda...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Cicho bądź, kamracie. Jak ci na imię, co? Jakoś umknęło mi to z pamięci...";
			link.l1 = "Kapitanie "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Słuchaj, "+pchar.name+". Dichoso zabił biednego Blaze'a. Widziałem to na własne oczy, tak-tak. Ale oni mi nie wierzą. Widzisz, myślą, że jestem szalony. Jeden z nich, ale szalony. A ja byłem najlepszym abordażystą w załodze samego Nicolasa Sharpa! Dobre czasy! Ale w końcu straciłem swoje pazury, kopyto i soczewkę i zostałem uziemiony.\nCo? Ach, racja! Wszyscy myśleli, że to wina Rekina, ale tak nie było. Nie-nie-nie. Był tam ząb rekina, talizman Dodsona, ale to Dichoso go tam podłożył.\nMusiał go ukraść Rekinowi, gdy razem pływali na fregacie zwanej Fortune. Tego dnia źle spałem i wyszedłem na spacer. Widziałem, jak Dichoso zakradł się do rezydencji Sharpa, słyszałem, jak ktoś krzyczał, a potem jęczał. Wkrótce po tym, jak Dichoso opuścił rezydencję, jego ręce były we krwi.\nNie uwierzyli mi, nie-nie. Bo tego dnia nie było Dichoso na wyspie, ale był Rekin. I znaleźli jego ząb. Ale widziałem Dichoso, jestem tego pewien. Nikt nie wiedział, że tam był tego dnia. 'Szczęściarz' to bardzo przebiegły i budzący strach mężczyzna...";
			link.l1 = "Nie jesteś pierwszym, który nazywa Dichoso 'Szczęśliwym'. Dlaczego tak jest? Czy to jego przezwisko?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Czy nie znasz hiszpańskiego, chłopie? 'Dichoso' znaczy 'szczęśliwy' w papieskim języku. Szczęśliwy Miguel, Miguel Szczęśliwy. Tak się to nazywa.";
			link.l1 = "Miguel Szczęściarz?... Hm. To mi coś przypomina. Hm. Ta fraza brzmi tak znajomo...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Cóż, chociaż jego nazwisko to Dichoso, wciąż nie sądzę, że jest Hiszpanem. Nie, nie. Nie jest Hiszpanem. Choć wygląda jak Hiszpan.";
			link.l1 = "A więc kimże on może być? Anglikiem, Francuzem?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Nie o tym mówię, Żeglarzu... Och, wybacz mi, Kapitanie. Tak, Dichoso gawędzi po francusku całkiem wspaniale, nie gorzej niż ty. I po angielsku również. Jednak w jego żyłach płynie indiańska krew. Widziałem wielu takich ludzi w moim życiu. Nie widać tego na pierwszy rzut oka, ale jest półkrwi. Gwarantuję ci.";
			link.l1 = " Czy on mówi po indiańsku?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "O, diabli wiedzą. Może i tak. Chociaż, czekaj. Tak, robił! Ciągle wygłaszał dziwne zdania w jakimś osobliwym języku, robił straszną minę mędrca i nadmuchiwał policzki, gdy je wypowiadał. Na przykład, mówił coś takiego: cogito ergo sum! A potem wywracał oczami i szukał reakcji marynarzy. Albo wykrzykiwał tak: aut Caesar, aut nihil! Wypalał też wiele innych rzeczy. Nie pamiętam wszystkiego, co mówił.";
			link.l1 = "To nie jest język Indian. To łacina. Łacina... Łacina?! Święty kurwa!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Czemu taki nerwowy, człowieku? Czemu krzyczysz? Ugryzł cię wąż czy co? Gdzie się podział?";
			link.l1 = "Czemu tego nie zauważyłem na początku! Wszystko było tuż przed moim nosem! Łacina! Miguel... Miguel Szczęściarz!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Hej, kumplu. Przestań już wrzeszczeć. Ludzie się na nas gapią. Co cię gryzie, Żeglarzu... przepraszam, Kapitanie?";
			link.l1 = "Ja wiem, kim naprawdę jest Miguel Dichoso. On nie jest Hiszpanem. On jest Francuzem! Ach, byłem tak ślepy!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "Nah-uh, głupcze. On nie jest Francuzem. On jest półkrwi. Jego biały tatuś zatańczył w butach z małą indiańską dziewczynką, jedną z tych Arawaków lub Miskito z Karaibów lub nawet Itza, i tak oto Święty Miguel Dichoso pojawił się na tym świecie. Ty tego nie widzisz, ale ja to widzę. To jest napisane w jego oczach...";
			link.l1 = "Zostawmy na chwilę kwestię jego pochodzenia. Gdzie on jest, Abrahamie?! Był tu?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "S-sz... Tak, on tu był. Ale odszedł. Nie ma go już na Isla Tesoro.";
			link.l1 = "Po co tu przyszedł? Jaki ma statek?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "Jego statek to galeon. Wielki wojenny galeon. Po co tu przybył... Cóż, kręcił się, zadając pytania. Ale podsłuchałem jego rozmowy, tak, tak! Szukał jakiegoś Charlesa de Maure. Tak, to właśnie to. Charles de Maure. Czekaj, to ty, Charles de Maure! Szukał ciebie, kumplu.";
			link.l1 = "Czy wiesz, po co?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Cóż, zdecydowanie nie po to, by odwiedzić tawernę i sączyć rum z tobą. On zamierzał cię pojmać. Tak, tak! Pojmać cię! Jesteś w głębokim bagnie, kapitanie!";
			link.l1 = "Nie wątpię w to...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "A ty? Dlaczego go szukasz? Och, rozumiem, rozumiem: żeby go zabić! Zabić go, zabić drania! Pomścić Blaze'a Sharpa! Blaze był wspaniałym facetem. Pamiętam go, nawet jako dziecko był taki jak Nicholas.";
			link.l1 = "Gdzie podział się Dichoso?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "Był w drodze do Blueweld. Powiedział, że Charles de Maure ma być szukany pod skrzydłem Leśnego Diabła. Ale zostawił tu swoich ludzi... Czekaj. Myślę, że już cię zauważono!";
			link.l1 = "Kto mnie zauważył?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Ludzie Dichoso. Kazał postawić tu na ciebie straż. Och, wiem, wiem! Bądź czujny, kapitanie: rafy Isla Tesoro otoczone są statkami i czekają tam na twoją głowę. Kapitan jest chytry jak lis. Nie daj się oszukać.";
			link.l1 = "Spróbuję...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "A jeszcze jedno: tutaj, weź moją szablę kawaleryjską. Weź ją, weź. Przyda ci się. To jest miecz samego Kapitana Barbariga. To znakomite ostrze. Najlepsze na archipelagu. Nie krępuj się, weź je. Blaze Sharp zostanie pomszczony!";
			link.l1 = "Dziękuję, Abrahamie.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Idź teraz. Idź, jesteś obserwowany. Spraw, by wyglądało, że jesteś mądry. Lub głupi. To bez znaczenia. Po prostu bądź ostrożny!";
			link.l1 = "Dzięki, kumplu. Nawet nie wiesz, jak bardzo mi pomogłeś. Powodzenia!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
