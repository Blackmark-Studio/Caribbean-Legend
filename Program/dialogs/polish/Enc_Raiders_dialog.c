void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Słyszałeś? Lokalny złodziej " + GetFullName(npchar) + " znalazł nową ofiarę. Jeden kapitan się przestraszył i przekupił bandyte. Mówią, że dał mu " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Tak, kapitanie " + GetFullName(pchar) + ", Już słyszałem, że musiałeś zapłacić " + FindRussianMoneyString(iMoney) + ", przekupić lokalnego bandytę, " + GetFullName(npchar) + ". To jest to, co nazywam pechem! Ha-ha-ha!", 
				"Czy słyszałeś, że lokalni bandyci zaatakowali jednego kapitana? Został całkowicie okradziony, stracił " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Słyszałeś? Tego bandytę " + GetFullName(npchar) + " wreszcie dopadła sprawiedliwość. On i jego chłopcy próbowali okraść "+ GetSexPhrase("jakiegoś kapitana, ale okazało się, że jest całkiem dobry","jakąś pani kapitan, ale okazało się, że jest całkiem dobra") +". Więc nasz drogi złodziej nasrał w spodnie, ha-ha! To będzie dla niego nauczka! Okradanie lokalnych farmerów to jedno, ale odważny kapitan to zupełnie inna historia!", 
				"Dziękuję, kapitanie " + GetFullName(pchar) + ", za to, że w końcu rozprawiłeś się z gangiem tego bandyty " + GetFullName(npchar) + ". Ci łobuziaki byli naprawdę utrapieniem dla wszystkich. Baliśmy się nawet wysyłać kurierów na farmę po mleko, mogliby ich przechwycić i okraść ze wszystkich pieniędzy."), 
				"Słyszałeś? "+ GetSexPhrase("Wreszcie jakiś kapitan powstrzymał","Nareszcie jakaś pani kapitan powstrzymała") +" tego drania " + GetFullName(npchar) + ", który był 'władcą' dżungli, terroryzując wszystkich lokalnych farmerów. Mam nadzieję, że powstrzyma ich to od brudnych uczynków na wystarczająco długo...", 
				"Słyszałeś o tym? lokalny bandyta " + GetFullName(npchar) + "  i jego chłopcy próbowali okraść "+ GetSexPhrase("jakiegoś kapitana","jakąś panią kapitan") +"? Bah! Nic takiego! Ten kapitan okazał się twardym orzechem do zgryzienia. Mówią, że gonił tych rabusiów po całej dżungli, jak rekin goni stado sardynek. Dzięki Bogu, że są jeszcze ludzie, którzy potrafią nas bronić w czasie, gdy władze nic nie robią, zbyt zajęte swoimi ciemnymi uczynkami..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Stań tam, gdzie jesteś i upuść broń! Twoje pieniądze albo twoje życie!","Stój tam, gdzie jesteś, "+GetSexPhrase("podróżniku","dziewczyno")+"!) Nie dotykaj swojej broni i żadnych gwałtownych ruchów!","Stój tam, gdzie jesteś, "+GetSexPhrase("podróżniku","dziewczyno")+"! To jest droga płatna. Jeśli chcesz przejść, płacisz myto."),LinkRandPhrase("Hej, "+GetSexPhrase("kolego","dziewczyno")+"! Nie tak szybko! Chcę zobaczyć, jak ciężka jest twoja sakiewka.","Czy mógłbyś podejść bliżej, przyjacielu. Chcę usłyszeć brzęk złota w twojej sakiewce.","Zaczekaj, "+GetSexPhrase("kumplu","dziewczyno")+". Ja i moi kumple założyliśmy się, ile złota zmieści się w twoim portfelu. Musimy to teraz sprawdzić, zanim sytuacja stanie się brutalna."),"Nie śpiesz się, "+GetSexPhrase("podróżniku","kochanie")+"! Porozmawiajmy szczerze, dobrze?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Dlaczego wygadujesz te bzdury?","O co chodzi?","O czym ty mówisz?"),"Co masz na myśli?","Co właściwie sugerujesz?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Rozbójnicy?! Świetnie, tęskniłem za walką!","O, wy jesteście bandytami! Ukrywacie się przed sprawiedliwością, tak? Cóż, wygląda na to, że sprawiedliwość właśnie po was przyszła...","Czy nikt ci nie nauczył, że przeszkadzanie obcym swoim nonsensem to przejaw złych manier? Wygląda na to, że muszę cię tej lekcji nauczyć..."),LinkRandPhrase("Och, jesteś bezczelny, czyż nie?! Mam nadzieję, że twój miecz jest tak ostry jak twój język.","Widzę, że jesteś mistrzem swojego języka, mam nadzieję, że jesteś też mistrzem swojego miecza.","Oh, bandyci! Tylu z was powieszono, lecz wciąż pchacie się w kierunku szubienicy."),LinkRandPhrase(RandPhraseSimple("O, bandyci! Wiesz, zazwyczaj nie marnuję słów na twojego rodzaju!","Co za bezczelny jegomość! Śmierdzi jak parująca gówniana góra i nadal ośmiela się zwracać do porządne"+GetSexPhrase("go gościa","j dziewczyny")+"."),"Nie będę marnować na ciebie słów, ale zobaczysz, że mój pistolet jest bardzo wymowny!","Znowu bandyci! Cóż, nie obiecuję ci szubienicy, ale na pewno mogę zrobić ci kilka dziur w brzuchu!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("A czy wiesz, że śledzi mnie lokalny patrol? Wystarczy, że zapiszczę i jesteś skończony.",RandPhraseSimple("Wiesz, mogę wezwać patrol, czyżbyś się tego nie bał? Są niedaleko. Przypuszczam, że szukają właśnie ciebie.","Patrol został niedawno wysłany, aby cię znaleźć, i będą tu za chwilę. Podejmujesz wielkie ryzyko."),RandPhraseSimple("Radziłbym ci uciekać jak najszybciej. Patrole idą w tym kierunku, właśnie rozmawiałem z ich oficerem.","Chętnie bym kontynuował naszą rozmowę, ale obawiam się, że patrol, na który właśnie się natknąłem, nie pozwoli naszej znajomości przerodzić się w bliską przyjaźń."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Nie udawaj głupka! Gotówka na miejscu i może wtedy cię wypuszczę!","Czy nie słyszałeś o opłacie wędrowca? Jeśli nie rozstaniesz się ze swoim złotem, rozstaniesz się z głową!","Heh, ta zwyczajna przygoda będzie cię kosztować sakiewkę... jeśli się nie zezłocę."),RandPhraseSimple("To bardzo proste. Oddajesz nam całe swoje złoto, a potem możesz swobodnie odejść, albo tu zostaniesz, a my i tak zabierzemy całe twoje złoto. Ale myślę, że to drugie ci się nie spodoba, he-he.","Nie udawaj, że nie rozumiesz! Daj mi swoją sakiewkę, jeśli nie chcesz, żebym zabrał jej z twojego martwego ciała!"),"Wyjaśnię, jeśli jesteś takim tępakiem. Dasz mi wszystkie swoje pieniądze, jeśli cenisz swoje życie.");
			Link.l1 = "Cholera jasna! Mam tylko "+makeint(makeint(Pchar.money)/20)*10+" pesos.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Chcesz moje pieniądze? Podejdź i weź je, a zobaczę, ile jesteś wart!","Jak śmiesz, chamie! Nauczę cię dobrych manier!","Jakie samozaparcie! No dobrze, zobaczymy, jak sobie poradzisz przeciwko prawdziwe"+GetSexPhrase("mu wilkowi morskiemu","j wilczycy mórz")+"!"),LinkRandPhrase("Powinieneś być chłostany za takie oburzenie!","Wy łotry! Módlcie się do swoich diabłów o ciepłe miejsce w piekle!","Dawno temu powinniście zostali powieszeni, szubrawcy! Cóż, wygląda na to, że będę musiał poplamić moją szablę waszą krwią!"),RandPhraseSimple("A co cię skłoniło myśleć, że dam ci moje pieniądze?","A czy nie zauważyłeś, że jestem dobrze uzbrojony i nie przyszedłem tutaj na prosty spacer?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Cholera! Dobrze, możesz iść. Ale nawet nie myśl o robieniu hałasu, kiedy tu jesteś!","Tym razem ci się poszczęściło, ale następnym razem będziesz nam dłużny dwukrotnie więcej! Nie zapomnij nam przypomnieć, he-he.");
				Link.l1 = RandPhraseSimple("Ależ oczywiście.","Uciekaj już, póki jeszcze możesz.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("Zabijemy cię po cichu, nawet nie pisniesz.","Cholera! Będziemy musieli cię szybko zabić, zanim podniesiesz alarm.");
					Link.l1 = "Cóż, to jest twój pogrzeb. Ostrzegałem cię.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("I dlaczego miałbym się przejmować twoim patrolem? Ja im płacę. Więc daj mi swój portfel i przestań gadać.","Myślisz, że mnie przestraszysz? Sam jestem 'patrolem' dla takich jak ty w tej dżungli. Nikt jeszcze nie wyszedł bez opłaty!");
					Link.l1 = "Cholera jasna! Mam tylko "+makeint(makeint(Pchar.money)/20)*10+" pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("He-h, nie zamierzam przestrzegać poleceń od takiego słabeusza jak ty.","Zrobię ci kilka nowych dziur w czaszce z powodu takiej bezczelności! Tylko aby trochę przewietrzyć twój mózg.","Taka bezczelność nie zostanie bez kary!"),"Nie powinieneś tego robić...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Hej, nie denerwuj się tak, "+GetSexPhrase("przyjacielu","dziewczyno")+"! To był tylko żart! Możesz kontynuować swoją drogę!","Dobrze, zmieniłem zdanie. Możesz iść, jeśli jesteś tak groźny."),"Co, znowu t"+GetSexPhrase("en dzielny kapitan","a wojownicza dziewczyna")+"? Dobrze, idź w pokoju...","Spokojnie, "+GetSexPhrase("kolego","dziewczyno")+". Widzisz, zaszła pomyłka, "+GetSexPhrase("myśleliśmy, że jesteś kupcem","myśleliśmy, że jesteś kupcem")+". Możesz iść.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Dobrze, do zobaczenia!","Powinieneś przestać okradać ludzi, póki jeszcze możesz.","Dobrze, ale jeśli kiedykolwiek cię znowu zobaczę..."),RandPhraseSimple("Następnym razem zwracaj uwagę, komu grozisz, szczeniaku.","Dzięki Bogu, że dzisiaj jestem w dobrym humorze."),RandPhraseSimple("Ten kryminalny handel na pewno cię w końcu zabije. Żegnaj.","To mądra decyzja. No cóż, powodzenia!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("Nie, kumpel. Teraz nauczę cię dobrych manier!","O, przestraszyłeś się? Cóż, powinno się odpowiadać za swoje czyny, prawda?","Nie! Teraz nie uspokoję się, dopóki nie obdzieję cię ze skóry na żywo!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("I mógłbyś odejść w pokoju! Teraz możesz tylko obwiniać siebie!","Nie powinieneś tego zaczynać, łotrze! Teraz zginiesz jak pies!","Och, dobrze! Porwę cię na kawałki! Wytnę wątrobę i nakarmię psy!");
				Link.l1 = RandPhraseSimple("Zatłukę twoje słowa z powrotem w twoje gardło!","Komu grozisz, łotrzyku?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Dobrze! Daj mi to i znikaj!","Nie wiele, ale zawsze lepiej niż nic. Dobrze jest mieć do czynienia z mądrą osobą! Możesz iść."),"To już inna historia! Jak mówił mój przyjaciel 'zawsze dobrze jest słuchać mądrego człowieka, ale rozmowa z głupcem jest o wiele lepsza'! He-he!","W zamian za twoje złoto dam ci radę, nie powinieneś chodzić po dżungli, jeśli jesteś "+GetSexPhrase("takim tchórzem. Pij swój rum w karczmie, aby ty i twój portfel pozostali bezpieczni!","dziewczyną. Bycie okradzionym to nie najgorsze, co mogło ci się przytrafić.")+".");
				Link.l1 = "Bądź przeklęty!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "Zgaduję, że próbujesz mnie oszukać! Bez obaw, pogłaskam cię moim nożem, może coś spadnie.";
				Link.l1 = "Cholera!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("Ty znowu? Biegnij do swojej mamy, zanim się na ciebie pogniewam!","Co? Jeszcze nie dałeś mi całego swojego złota? Ha-ha!","Spójrz, "+GetSexPhrase("kumplu","dziewczyno")+", Mam cie dość! Znikaj mi z oczu, póki jeszcze żyjesz!");
			Link.l1 = "Tak, już odchodzę.";
			Link.l1.go = "Exit";
			Link.l2 = "Myślałem, że to nie byłoby sprawiedliwe. Dlatego postanowiłem naprawić rzeczy...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("Co jeszcze potrzebujesz? Już zgodziliśmy się, że odchodzisz!","Zostaw mnie w spokoju, "+GetSexPhrase("przyjacielu","dziewczyno")+". Zajmuję się swoimi sprawami, a ty swoimi i nie powinniśmy próbować dogadywać się!","Odejdź teraz, "+GetSexPhrase("kumplu","dziewczyno")+"! Do cholery, naprawdę jesteś gotów oddać całe swoje pieniądze?");
			Link.l1 = "Tak, już wychodzę.";
			Link.l1.go = "Exit";
			Link.l2 = "Przypomniałem sobie, że nie pożegnałeś się! Więc pożegnajmy się jak należy...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Zostaw mnie! Pomocy! Chcę żyć!","Pomocy! "+GetSexPhrase("On jest maniakiem","Ona jest maniaczką")+"! Nie zabijaj mnie!","Oszczędź mnie! Jestem tylko skromnym bandytą! Jestem zbyt młody, aby umierać!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Gdybyś został w domu, nadal byś żył!","Powinieneś był o tym pomyśleć wcześniej!","Powinieneś wiedzieć, że zawsze są konsekwencje!"),"Wcześniej czy później, to musiało się wydarzyć.","Za późno na pokutę, teraz walcz, szumowino!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
