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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Bug. Powiedz to deweloperom.";
		link.l1 = "Pewnie.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "O, kolejny odważny marynarz! Znam twój rodzaj, moje przeklęte przez Boga oko jest na ciebie wycelowane, ha! Zapytaj mnie dlaczego?";
			link.l1 = "Wole zapytać cię o inną sprawę, chodzi o twój dług, który jesteś winien pani miejscowego... hmm, przybytku. Poprosiła mnie, abym przypomniał ci o twoim długu, sugeruję, żebyś coś z tym zrobił, w przeciwnym razie będzie musiała zwrócić się do straży, aby jutro ci o tym przypomnieli.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Właścicielką jest... o, kurwa! Johanna, nie może mi tego zrobić! Jesteś pewien? Czy naprawdę powiedziała, że wyśle mnie do kazamatów za kilka cholernych monet?";
			link.l1 = "Oczywiście. Tak właśnie powiedziała. Sądzę, że moja misja dobiegła końca, żegnaj, panie Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Zaczekaj! Proszę, zaczekaj! Wyglądasz na doświadczonego kapitana. Z pewnością masz trochę monet, jestem spłukany, tylko dobry stary barman napełnia mój kielich na kredyt dla naszej starej przyjaźni. Posłuchaj mojej... propozycji! Spłacisz mój dług, a ja cię odwdzięczę\nJest interes... bardzo dochodowy interes, chrzanić mnie i moją dupę! Przysięgam na moją krwawą kotwicę, tylko mi zaufaj, kapitanie - jakkolwiek się nazywasz!\nWystarczy, że wykupisz jeden mały dług, dziesięć tysięcy pesos, a będziesz miał szansę zarobić wystarczająco dużo monet, by kupić wszystkie burdele Nowego-krwawego-Świata! Co ty na to? Ty mi dasz kawałek, ja ci dam kawałek, jak uczciwi ludzie robią...";
			link.l1 = "Obszarpany facet, który obiecuje skarby. Oszczędź mi tych bzdur, nie prowadzę dobroczynności dla takich jak ty. Znajdź pieniądze albo wkrótce zamieszkasz w kazamatach fortu. Żegnaj!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Kawałek? A dlaczego miałbym ufać słowu pijanego idioty? Ze względu na wymyślone obietnice?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Słuchaj mnie, kapitanie! Hik, zastrzel mnie, jeśli kłamię! Ale mówię prawdę! Pomyśl o tym, jeśli złapiesz mnie na kłamstwie, to wyprujesz mi flaki tą pięknością, którą nosisz przy pasie! Cholera, jej rękojeść kosztuje pięć razy więcej niż mój nędzny dług! Więc co powiesz? Nie masz nic do stracenia!";
			link.l1 = "Mam dość twoich przemówień. Żegnaj.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = " Dobrze, Hugo... Zaryzykuję i uwierzę w te bzdury, które wygadujesz. Ale pamiętaj, że będziesz musiał mnie przekonać i upewnić się, że moje pieniądze nie poszły na marne, gdy wrócę, inaczej to twoja głowa będzie na szali.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Nie potrzeba gróźb, rozumiem. Daję ci moje słowo, kapitanie! Będziemy bogaci! Wróć, gdy ten cholerny dług zostanie spłacony, a porozmawiamy! Tak, porozmawiamy! Nie zostaniesz pominięty!";
			link.l1 = "Zgoda, daruję ci dług, ale lepiej módl się, Hugo Avendell, żeby twoja 'propozycja' mnie zadowoliła.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Kapitanie, wracaj tak szybko, jak możesz - ten interes może się wymknąć.";
			link.l1 = "Tak, tak, wkrótce spłacę twój dług.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Wracasz, kapitanie! Na burzę i niech to piorun trzaśnie, jakże się cieszę, że cię widzę! Co z moim długiem?";
			link.l1 = "Załatwiłem to, teraz twoja kolej, Hugo. Opowiedz swoją historię i postaraj się, by była choć trochę wiarygodna!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Nie martw się, kapitanie! Czy wiesz, że jestem łowcą nagród? A raczej... byłem. Nie miałem chyba dość szczęścia. Może sam Diabeł ze wszystkimi swoimi uczynkami nie był takim nieudacznikiem jak ja. Straciłem wszystko na moim ostatnim zleceniu... Załoga uciekła, a ja musiałem sprzedać swój statek z powodu długów...";
			link.l1 = "Jestem już poinformowany o twojej bohaterskiej przeszłości. Przejdźmy do interesów, Hugo, nie wystawiaj mojej cierpliwości na próbę.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Tak, tak, kapitanie..."+GetFullName(pchar)+", czy mam rację? Wiem też coś o tobie. Ale niech mnie diabli, jeśli to ważne. Czy słyszałeś o Bartolomeo Portugalczyku?";
			link.l1 = "Bart Portugalczyk? Oczywiście, że o nim słyszałem. Każdy słyszał. To pirat, rzeźnik i łajdak, o ile wiem. A jaki jest jego udział w twojej opowieści?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "On bierze w tym cholerną główną rolę! Śledziłem go przez ostatnie półtorej roku. Holenderska Kompania wyznaczyła wielką nagrodę za jego głowę. Ale zawiodłem, i straciłem wszystko. A Kompania potroiła niedawno nagrodę za niego żywego i tylko żywego, do diabła z nim!";
			link.l1 = "Nie bez powodu, nie jest łatwo pojmać go żywcem. Tak czy inaczej, dlaczego miałbym się tym przejmować, Hugo? Wygląda na to, że próbujesz mnie wykiwać!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "Nie miałem nawet zamiaru, kapitanie! Wiesz, miejscowy doktor Peter Van Stal, bardzo miły człowiek, dał mi miksturę na bóle głowy! Więc doktora nie było w jego domu przez prawie trzy dni i...";
			link.l1 = "Hugo, moja cierpliwość się kończy! Obiecałem damie, że nie przebiję cię sztyletem, ale moje pięści będą równie skuteczne! Przysięgam, że żadna mikstura nie uleczy jutro twej głowy!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Poczekaj, kapitanie! Proszę! Posłuchaj mnie, widziałem kilku ludzi w pobliżu domu doktora i ich rozpoznałem. Są z 'Albatrosa', statku przeklętych Portugalczyków! I jeden z nich mówił o zdrowiu swojego kapitana! Zobacz teraz, "+pchar.name+", Bartolomeo jest tutaj, w tym mieście! Tuż pod naszymi nosami, jest albo ranny, albo chory, dlatego potrzebują przeklętego lekarza!\nWątpię, żeby ten Portugalczyk przyprowadził tu całą swoją załogę, ale nie mogę zacząć tej rozróby sam! Na pewno, do cholery, wiesz, jak posługiwać się swoją przeklętą szablą! Weź ze sobą kilku twardzieli i znajdziemy tego szczura! Potem go pojmiemy i dostarczymy władzom!\nA dwa tysiące dobrych złotych dublonów trafi do naszych kieszeni!";
			link.l1 = "Nie, Hugo, mam dość twojego gadania. Nie wezmę udziału w tym bałaganie, nawet jeśli masz rację. Żegnaj.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, interesujące. Wiesz, gdzie się ukrywa? Jeśli się uda, możemy omówić udziały, ale jeśli mówisz prawdę, to musimy się teraz pospieszyć!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "Nie, nie wiem, gdzie on jest, kapitanie. Bałem się za bardzo, by śledzić tych chłopaków. Gdyby Jednooki mnie zobaczył... ohyda! Ale razem, plus twoi chłopcy, będziemy w stanie przeczesać całe to miasto, zawołaj swoich ludzi i zaczynajmy! Cholera, holenderskie dublony na nas czekają! Taka przeklęta okazja zdarza się tylko raz w życiu, niech mnie śledź ugryzie!";
			link.l1 = "Coż za entuzjazm... Mam nadzieję, że potrafisz oderwać się od stołu, 'wielki' łowco nagród. Idę szukać natychmiast, a ty możesz podążać za mną, jeśli chcesz, tylko nie przeszkadzaj mi zbytnio.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Tak, tak, kapitanie, tylko pozwól mi dokończyć mój napitek, a dołączę do ciebie... Gdzie zaczniemy?";
			link.l1 = "Gdzie?!... Idę, z tobą lub bez ciebie.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Zły dom, kolego. Zjeżdżaj stąd, teraz!";
			link.l1 = "Hm. A ja myślę, że to właściwy dom...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Cóż, ostrzegałem cię...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Pełny i bystry, wysoko latający, chłopcy... przygotować działa!... ah-ha-ha... o moja piękności...";
			link.l1 = "Hmm, ma szczęście, że żyje...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "O Boże, kim jesteś? Proszę, odłóż broń! Jest tu chory człowiek!";
			link.l1 = "Ten 'chory człowiek' zabił więcej ludzi, niż widziałeś w swoim życiu, doktorze. Odejdź!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "On jest moim pacjentem i nawet nie jest w stanie stać! Nie widzisz tego? Proszę, opuść swój miecz! Błagam cię!";
			link.l1 = "A co z nim nie tak, do cholery!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Przypuszczam, że to wszystko przez jego ranę, cios zadany zatrutą bronią Karaiba... a ludzie, którzy go tu przywieźli, powiedzieli, że jeśli on umrze, to ja też! Dlatego robię wszystko, co w mojej mocy, powiedz im to!";
			link.l1 = "Nie martw się o tych ludzi, doktorze. Moi chłopcy będą mieli oko na twój dom, a ja muszę iść do gubernatora. Przypuszczam, że zesra się z radości. Nie opuszczaj tego miejsca, dopóki nie wrócę, doktorku.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Nie odejdę, nie martw się o to. Oddajmy go już władzom i zakończmy ten koszmar.";
			link.l1 = "Oczywiście, już idę.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "Zrobiliśmy to, kapitanie! Znaleźliśmy go i wkrótce będziemy bogaci, tak jak ci mówiłem! Jaki jest nasz plan?";
			link.l1 = "Mam nadzieję, Hugo. W każdym razie, to jeszcze nie koniec. Przypuszczam, że muszę udać się do gubernatora i omówić naszą nagrodę?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "Nie, nie, kapitanie! Nie idź do tego przeklętego Thomasa! Uwierz mi, ten łajdak odbierze nam naszego więźnia i jeśli będziemy mieli szczęście, poczęstuje nas filiżanką kawy! Jego Ekscelencja to podejrzany typ, więc jeśli chcesz dostać pełną nagrodę, musisz popłynąć na Kurakao! W przeciwnym razie Portugalczyka zabiorą do fortu i przegonią nas jak żebraków!";
			link.l1 = "Cóż, jeśli naprawdę jesteś tego pewien...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Jestem, kapitanie, do diabła, że jestem! Ale pamiętaj, że ludzie Bartolomeo muszą być gdzieś w mieście i na pewno nie chcemy przyciągać uwagi garnizonu! Musimy zdecydować, jak dostać Portugalczyka na twój statek i jak to zrobić w niezauważalny sposób.";
			link.l1 = "Niech będzie... Nie chcę walczyć z jego okrętem w drodze do Willemstad. Masz jakieś pomysły?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Tak, mam jeden. Najpierw musimy znaleźć dla niego bardziej szlachetny strój, a potem przeciągniemy go przez tylne wejście jako pijanego oficera! Nikt nie będzie podejrzewać, że to cholerny pirat, zaufaj mi!";
			link.l1 = "Hmm, nie jestem co do tego pewien, ale nie mamy jeszcze lepszego planu. Spróbuję zdobyć jakieś ładne tkaniny dla naszego pasażera. Ty zostań tutaj i pilnuj Barta i doktora.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Nie martw się, kapitanie. Portugalczyk jest pod moją niezawodną strażą, he-he...";
			link.l1 = "Właśnie widzę...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Nie widzę żołnierzy, "+GetAddress_Form(NPChar)+". Gdzie oni są? Powiedziałeś, że zostanie aresztowany, jak tylko opowiesz im o sytuacji. Dlaczego więc żołnierzy tu nie ma?";
			link.l1 = "Nie będzie żadnych żołnierzy, mynheer Van Stal. Zamierzam wykonać zadanie sam i muszę jak najszybciej zabrać twojego pacjenta na Kurakao.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Kapitanie, słuchaj, nie mogę sobie poradzić z jego raną, mogę tylko trochę zbić gorączkę. Jest głównie nieprzytomny i majaczy, nie ma wątpliwości, że umrze nawet bez żadnej ingerencji, a kołysanie morza zabije go w ciągu kilku dni. Dam ci kilka mikstur, które pomogą...";
			link.l1 = "Nie, doktorku, płyniesz z nami. Po pierwsze, nie znam się na medycynie, a po drugie, wątpię, byś chciał zostać tutaj i tłumaczyć Portugalczykom, gdzie podział się ich kapitan?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Tak, przypuszczam, że masz rację. Ale wiedz, że ten pirat jest bardzo odporny, widziałem ludzi z tylko małymi zadrapaniami od indiańskich broni i wszyscy zmarli w mniej niż trzy dni. A według jego 'przyjaciół', jest w tym stanie już od tygodnia! Niemniej jednak, twierdzę, że przeżyje krótki okres czasu na statku na otwartym morzu. Trzy dni, nie dłużej!\nTo cały czas, jaki mamy.";
			link.l1 = "Nawet ptak nie dotrze do Kurakao w trzy dni.  Ale myślę, że wiem, co mogę zrobić! Jest taki... mój przyjaciel, mieszka w St. John's, na Antigui. Zna się na leczeniu ludzi z śmiertelnych ran. Jest jedyną osobą, która może nam teraz pomóc. Nasz cel jest prosty - dotrzeć tam, zanim Portugalczyk umrze. Spakuj swoje rzeczy, doktorze, natychmiast wyruszamy, a twój pacjent zostanie przeniesiony jako następny!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Co za szkoda, kapitanie. Przegraliśmy, i nie zobaczymy tego przeklętego złota. Żegnaj.";
			link.l1 = "Żegnaj, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doktorze, przygotuj pacjenta do transportu. Szalupa jest gotowa. Pośpiesz się!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Jestem w drodze, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "Ten dom cuchnie pieprzonymi miksturami! Byłoby wielkim zaskoczeniem, gdyby Portugalczyk umarł tutaj, nawet oddychanie tym zapachem może wyleczyć każdą chorobę!\nA załoga tego człowieka może nas łatwo znaleźć dzięki temu smrodowi!";
			link.l1 = "Hugo, oszczędź mi swoich żartów, bo brzmią bardziej jak suchary. Zostawiłem kilku ludzi na ulicach, aby pilnowali domu, ale jeden dodatkowy strażnik nie zaszkodzi naszemu gościowi. Miej na niego oko i spróbuj powstrzymać przeklinanie, bo Gino zmusi cię do wypicia jakiejś swojej mikstury, jestem pewien, że potrafi to wyleczyć.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Nie martw się, kapitanie! Będę pilnował naszych pieniędzy najczujniej, jak tylko można, nie ucieknie nawet, gdyby był zdrowy! I proszę cię, błagam, żadnych mikstur!";
			link.l1 = "Widzisz, potrafisz być miły, kiedy chcesz. Bądź czujny, muszę iść.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Już wychodzisz, kapitanie? Świetnie! Czas najwyższy! Widziałem kilku podejrzanych typów na ulicy. Nie wyglądają na Portugalczyków, choć czegoś szukali, musimy być ostrożni, kapitanie!";
			link.l1 = "W porządku, dzięki za ostrzeżenie, Hugo. Chodźmy na statek.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Kapitanie, czekaliśmy na to spotkanie zbyt długo! A kto to z tobą? Bartolomeo sam Portugalczyk, ha, wygląda na to, że Śmiały Pierre miał rację - to on! Trzymaj się z dala, kapitanie, zamierzamy zabrać go ze sobą i nikt nie ucierpi.";
			link.l1 = "Przepraszam panie, ale kim do cholery jesteś? Zejdź mi z drogi, albo żaden z was nie doczeka jutra!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, cóż za groźny człek, spójrzcie na niego chłopaki! Ha-ha-ha! Słuchaj no, szczeniaku, nie stawaj między Leo Cordem a jego pieniędzmi! Ścigamy tego Portugalczyka już prawie pół roku i teraz wreszcie go mamy. Więc odłóż tę twoją wykałaczkę i zniknij, póki jeszcze oddychasz! Nie jesteśmy aż tak chciwi, martwy człowiek też będzie w porządku, ha-ha!";
			link.l1 = "Dość. Zatańczmy, panowie!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = " Wiedziałem, że coś tu jest nie tak! Dobra robota, kapitanie! Ale czas się zbierać, ten cholerny Leo Cord ma tu mnóstwo bandytów i porządną łajbę! Musimy uciekać z tej wyspy!";
				link.l1 = "Dobry punkt, Hugo, i bardzo się cieszę, że żadna kula nie została wystrzelona w dziurę, w której się ukrywałeś.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Jaka szkoda, kapitanie. Przegraliśmy i nie zobaczymy tego przeklętego złota. Żegnaj.";
				link.l1 = "Żegnaj, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "Ja... Ja zabezpieczałem nasz tył, kapitanie! Poradziłeś sobie doskonale beze mnie, ale co gdyby ktoś zaatakował nas z drugiej strony ulicy? Nie miałyś czasu, by pobiec na statek.";
			link.l1 = "Być może dlatego nie odniosłeś sukcesu w swoim fachu? Nieważne, dość gadania, musimy dostać się na statek! Czas ucieka!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Kapitanie, Portugalczyk czuje się naprawdę źle, musimy się zatrzymać!";
			link.l1 = "To dlatego jesteśmy tutaj, panie van Stal, nasza podróż prawie się kończy. Wynajmę pokój w karczmie, a nasz więzień zostanie tam na kilka dni.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Mynheer kapitanie, będę się opiekować Portugalczykiem, potrzebuje pełnego odpoczynku.";
			link.l1 = "Dobra, doktorku, w porządku. Cholera, jak długo mam się opiekować tym piratem? To niedobrze, to nie jest to, czego potrzebuje! Wydaje się, że zostałem zatrudniony jako niańka i... agh, przepraszam, doktorze, to po prostu za dużo... Zobaczymy się później.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Panie, czy jesteś kapitanem "+GetFullName(pchar)+", którego statek właśnie dziś przybył do naszego portu?";
			link.l1 = "Masz rację, jak mogę ci pomóc?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Jego Ekscelencja Jacques Dille du Parquet, gubernator naszej kolonii czeka na ciebie. Sprawa jest pilna!";
			link.l1 = "Dobrze, monsieur, odwiedzę jego Ekscelencję dziś.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Dotarliśmy do Martyniki, kapitanie! Nasze pieniądze są teraz niedaleko...";
			link.l1 = "Jeśli tylko Portugalczyk dożyje, aż dotrzemy do Willemstad. Hugo, muszę iść na statek, więc będziesz musiał pilnować doktora i jego pacjenta.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "Do statku? Dlaczego? Pożyczysz mi kilku swoich ludzi, żeby mi pomogli? A co jeśli coś się stanie, gdy cię nie będzie?";
			link.l1 = "Przykro mi, ale nie. Wątpię, by cokolwiek mogło ci tu zagrozić. Garnizon jest w stanie gotowości, a na ulicach jest więcej żołnierzy niż zwykle, więc jeśli coś pójdzie nie tak, wezwij ich. Widzieli duży statek niedaleko tej wyspy, piracki, być może. A Jego Ekscelencja gubernator poprosił mnie o wzmocnienie wyspy, patrolując ją moim statkiem.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Statek? Piracki? To mógłby być 'Albatross'! Albo jakiś kolega naszego starego przyjaciela Leo Corda!";
			link.l1 = "Albo może to po prostu zwykły piracki statek. Niemniej jednak, Hugo, jeśli ten okręt jest tutaj po nasze głowy, to lepiej stanę z nią twarzą w twarz z lokalnym patrolem u boku i dla złota gubernatora. To o wiele lepsze niż pilnowanie naszych tyłów przez resztę podróży. Jeśli jednak ten alarm jest fałszywy, oszczędzi mi to po prostu siedzenia na moim tyłku w karczmie przez kilka dni.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Pomyśl o tym, kapitanie, czy to mądre zostawiać tam... Portugalczyka bez ochrony, podczas gdy jego statek może krążyć w pobliżu? Ryzykujesz naszą nagrodę, przyjmując opłatę gubernatora!";
			link.l1 = "Dosyć gadania, Hugo Avendell! To ja jestem tutaj kapitanem i ostateczna decyzja należy do mnie! Więc rób, co ci rozkażę. Idź do karczmy i miej oko na doktora i Portugalczyka, dopóki nie wrócę.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Wracasz, kapitanie, nareszcie! Obawiam się, że mam dla ciebie złe wieści - Portugalczyk zniknął, a z nim i doktor!";
			link.l1 = "Jak to?! A co ty wtedy robiłeś, durniu?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Mogę się założyć, że ten statek to był 'Albatross'. Widziałem Portugalczyków, weszli do karczmy i ja... uciekłem. Przykro mi, ale spotkanie z Jednookim Psem to było za wiele nawet za takie pieniądze!";
			link.l1 = "Cholera! Powiedz mi chociaż, co się stało w karczmie?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Widziałem, że nic nie widziałem. Uciekłem przez kuchnię, jak tylko zobaczyłem Franza Garcke i jego ludzi... Było zbyt blisko! To się stało wczoraj wieczorem i nie wiedziałem, jak ci dać znać...";
			link.l1 = "Tak, jesteś bardzo odważnym i zaradnym człowiekiem... Dobrze, dajmy ci jeszcze jedną szansę, znajdziemy ich. Zbyt długo oszczędzałem tego łajdaka i teraz uważam go za swoją własność. Mamy jeszcze trochę czasu, żeby ich złapać, więc zacznijmy od karczmy, może ktoś widział więcej niż twoje uciekające pięty. Idź, przygotuj się!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Słyszałeś go, kapitanie, mówił o Jednookim Psie, wspominałem ci o nim ostatnio. A sepleniący Kastylijczyk to Hernando Vasquez, krwawy Don - rzeźnik z Vera Cruz, nie widziałem go!";
			link.l1 = "Spokojnie, Hugo. Jestem pewien, że Bartholomeo wciąż jest na wyspie, może się polepszył, ale nadal jest zbyt słaby. I myślę, że wiem, gdzie go znaleźć! Dorwiemy ich, nie zrezygnuję z mojej nagrody. Jeśli nie jesteś tchórzem, podążaj za mną, to jeszcze nie koniec.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Zadajesz za dużo pytań, kapitanie... Czekaj, czyżbyś nie był tym przebiegłym typem z Philipsburga? Uciekałeś przed nami zbyt długo, a teraz spójrz - oto jesteś...";
			link.l1 = "Za późno dla ciebie, szumowino!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... ty, parszywy gówniarzu, powiesz nam wszystko, możesz mi ufać, ty zasrany szczurze! Potem zostaniesz powieszony na rei zamiast na żaglu... A kimże ty, do diabła, jesteś? Cholera, tym małpom nie można ufać! Zawsze muszę wszystko robić sam...";
			link.l1 = "Czy przeszkadzam wam, panowie?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "Lubię twoje wyczucie czasu... Chyba muszę ci podziękować za to, że utrzymałeś mnie przez taki długi czas przy życiu?";
			link.l1 = "Masz rację. Nazywam się "+GetFullName(pchar)+" a ty, Portugalczyku, wciąż jesteś moim więźniem. Więc nie zadawaj mi pytań, musimy iść.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Poczekaj, kapitanie... w mieście jest wielu ludzi Vasqueza, nie pozwolą nam tak po prostu odejść. Daj mi miecz, a nasze szanse będą o wiele lepsze.";
			link.l1 = "Nie jesteś w dobrych stosunkach ze swoimi wspólnikami, co? Dobrze, dodatkowe ostrze zawsze się przyda, weź broń z trupa i trzymaj się blisko mnie!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Nie myśl sobie nawet, że dam ci broń, abyś mógł mnie uderzyć, gdy tylko odwrócę się do ciebie plecami! Po prostu trzymaj się blisko mnie.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Nie martw się, kapitanie, prędzej umrę, niż wpadnę znów w ręce Vasqueza.";
			link.l1 = "Cóż, chodzi o to, że jeszcze nie chcę cię martwego. Chodźmy, czas ucieka!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Szkoda, pomógłbym Jednookiemu, gdybym chciał cię martwego...";
			link.l1 = "Ale ty też mi nie pomogłeś, więc zamknij się i ruszaj!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Cholera! To oni! Zabijcie ich wszystkich!";
			link.l1 = "Znowu to samo... Chodźcie, wy kundle!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Znakomicie! Zabiłeś Jednookiego Psa, to nazywam arcydziełem! Ilu z jego ludzi wysłałeś, by spłonęli w piekle?";
				link.l1 = "Biłem się, nie licząc. A gdzieżeś był, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Jaka szkoda, kapitanie. Przegraliśmy i nie zobaczymy tego przeklętego złota. Żegnaj.";
				link.l1 = "Żegnaj, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Ja... zabezpieczałem bezpieczne wycofanie... chroniąc nasze tyły, że tak powiem.";
			link.l1 = "Dobra, mam juś tego dość, Hugo Avendell, twoje tchórzostwo przekroczyło wszelkie moje oczekiwania, masz pojęcie, jak ciężka była dla nas ta walka? Ledwo daliśmy radę!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Spokojnie, kapitanie... Przyznaję, ukrywałem się. Ale znalazłem dla ciebie tę okazję! Pamiętaj, to ja cię zaprowadziłem do Portugalczyków! Cóż... biorąc pod uwagę twoje słuszne oburzenie, zgadzam się na jedną trzecią nagrody.";
			link.l1 = "Toż to wspaniałe! Teraz się targujesz? Nie, mój przyjacielu, twoja rola w tym interesie dobiegła końca! Straciłeś pieniądze w karczmie w Saint-Pierre. Zostawiłeś je tam i uciekłeś, więc teraz to dla ciebie koniec.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Kapitanie, wyraźnie przesadzasz... Dobrze, zgadzam się na jedną czwartą... na jedną piątą! Dziesięć procent!";
			link.l1 = "Nie wystawiaj mojej cierpliwości na próbę! Zjeżdżaj! Nie potrzebuję tchórzy w mojej załodze, zwłaszcza teraz, gdy czas ucieka!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", czy nie uważasz, że to trochę niesprawiedliwe?";
			link.l1 = "Przyczyna i skutek, Hugo... Dokonałeś wyboru, więc żegnaj. Wyciągnij wnioski i nie rzucaj się w takie przygody, to wyraźnie nie dla ciebie.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Porzucasz balast, kapitanie? Prawda, ha... Vasquez wciąż jest wolny, a na Albatrosie jest wielu ludzi i dział, stawiam moje eleganckie spodnie przeciwko starej chustce, że Hernando nie pozwoli nam uciec.";
			link.l1 = "Cóż, wydaje się, że musimy sami go powitać. Idź, monsieur Portugalczyku, i spróbuj trzymać język za zębami. Będziemy podnosić kotwicę tak szybko, jak to możliwe.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "Na co czekasz, do diabła?!";
			link.l1 = "Gdzie jest Hernando Vasquez? Mów, a oszczędzę ci życie.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Idź do diabła z tymi cholernymi pytaniami!";
			link.l1 = "Dobra, ty pierwszy...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "I oto jesteś, mój odważny przyjacielu, wreszcie możemy porządnie porozmawiać! Gratulacje, kapitanie - zabicie Jednookiego Psa i zniszczenie 'Albatrosa' nie było łatwym zadaniem! Właściwie, zrobiłeś tak wiele, aby uratować moje życie... Być może, powinienem ci nawet podziękować?";
				link.l1 = "Podziękujesz mi, gdy będziesz tańczyć na szubienicy lub cokolwiek innego przygotowali dla ciebie w Willemstad.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "I oto jesteś, mój dzielny przyjacielu, wreszcie możemy porozmawiać! Gratulacje, kapitanie - zabicie Jednookiego Psa to zasługuje na honorową pieśń! W rzeczywistości zrobiłeś tak wiele, aby ocalić moje życie... Może nawet powinienem ci podziękować?";
				link.l1 = "Podziękujesz mi, gdy będziesz tańczył na szubienicy lub cokolwiek przygotowali dla ciebie w Willemstad.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Niewiarygodne! Ratujesz moje życie przez ostatnie dwa tygodnie, przywiozłeś mnie do swojego domu i chroniłeś w walkach... a teraz zamierzasz wysłać mnie na śmierć? Trudno mi w to uwierzyć... Właściwie, prawie uważam cię teraz za przyjaciela, ha-ha.";
			link.l1 = "Pirat, który apeluje o honor? Portugalczyku, czy żartujesz sobie ze mnie? Oszczędzałem cię tylko w jednym celu - aby morderca i łotr stanął przed sądem!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Przyjacielu mój... brzmi jak szyderstwo. Ale mimo to masz rację. Byłoby dziwne, gdybym to zrobił, Portugalczyku...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Och, dość, kapitanie. Założę się, że robiłeś to wszystko tylko po to, by zdobyć pieniądze, które obiecała Kompania za przyjemność ujrzenia mnie żywego! Nie próbuj być bardziej uczciwy, niż jesteś w rzeczywistości, sir, to do ciebie nie pasuje.";
			link.l1 = "Tylko ja mogę siebie osądzać. Więc zakończmy tę rozmowę. Czas żeglować do Willemstad.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Wydaje się, że wciąż można znaleźć trochę uczciwości w ludziach w dzisiejszych czasach... Szkoda, że pieniądze zawsze przeszkadzają - eh, kapitanie?";
			link.l1 = "Dziwne to słyszeć od pirata wisielca, Portugalczyku. Pozwolę ci odejść... nie pytaj mnie dlaczego, po prostu wynoś się do pierwszego portu. I pamiętaj, że nie będę taki łaskawy, jeśli jeszcze się spotkamy.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Naprawdę? Chciałbym tego, kapitanie! Czy nie rozkażesz przynieść tu trochę rumu? Wiesz, po prostu, aby uczcić twoje rycerskie cechy, nasze relacje i odroczenie mojego wyroku?";
			link.l1 = "Nie stroń niegodziwych żartów, wciąż jesteś moim więźniem aż do pierwszego brzegu. Żegnaj.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Rozumiem... a więc szubienica, co? Tego się spodziewałem. Posłuchaj więc, co ci powiem, kapitanie. Byłeś tak chętny, by utrzymać mnie przy życiu, aby później mnie należycie stracić, i doceniam to. Przypuszczam, że byłoby głupotą z mojej strony prosić cię, byś po prostu zmienił zdanie, prawda? A co powiesz, jeśli zaoferuję ci coś w zamian? Umowa, że tak powiem, co?";
			link.l1 = "Nic nie powiem, Portugalczyku. Jesteś piratem i draniem. Odpowiesz za swoje zbrodnie w Willemstad.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Umowa? Co możesz zaoferować?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Nie potrzebuję twojej umowy, po prostu zniknij w pierwszym porcie. To twój szczęśliwy dzień.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Wiesz, takie uparte ratowanie mojego życia pomimo nieprzyjemnych powodów, wciąż zasługuje na pewną wdzięczność. A Bartolomeo Portugalczyk wie coś o byciu wdzięcznym. Teraz posłuchaj, miesiąc przed tym jak się spotkaliśmy, przechwyciliśmy statek Kompanii. Walczyli jak diabły do ostatniego człowieka. Ale w ładowniach mieli tylko kule armatnie i szczury\nMojej załodze się to nie podobało, ale znalazłem bardzo interesującą skrzynię i papiery w kajucie kapitana. To był statek kurierski, dostarczający próbki z kopalni gdzieś w Amazonii. Czyste diamenty i rubiny, prawdziwa fortuna!";
			link.l1 = "Interesująca zdobycz... Teraz rozumiem, dlaczego Kompania jest tak tobą zainteresowana, ale jaki jest sens twojej opowieści?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "Moi pierwsi oficerowie Vazquez i Franz Garcke utrzymywali załogę w ryzach, więc postanowiłem zaryzykować. Ukryłem kamienie przed nimi i spaliłem dokumenty. Holendrzy poważnie uszkodzili nasze olinowanie podczas abordażu i musieliśmy wziąć 'Albatrossa' do małej zatoki na małej wyspie na północy. Sam poszedłem głębiej w dżungle, podczas gdy cała załoga naprawiała okręt. Zakopałem kamienie, trzymanie ich na pokładzie było zbyt ryzykowne w zaistniałych okolicznościach. Mój plan polegał na ucieczce z ukochanej załogi w pierwszym porcie, kupieniu lub kradzieży małej łodzi i wypłynięciu na wyspę, zbierając nagrodę, a potem... pożegnanie z moim starym życiem! Europa, porządna rezydencja, gorąca żona, znasz resztę...";
			link.l1 = "Niech zgadnę, coś poszło nie tak.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = " Wszystko poszło źle! Przeklęta wyspa okazała się ojczyzną hordy lokalnych kanibali. Zaatakowali nas, gdy tylko wróciłem na brzeg. Musieliśmy odpłynąć jak najszybciej, wtedy to zostałem trafiony. Myślałem, że to tylko zadrapanie.\nKilka dni później leżałem półmartwy w gorączce i podobno mówiłem coś o kamieniach. Franz i Vazquez zorientowali się, że ukryłem coś na wyspie, ale nie znali dokładnej lokalizacji. Nie podobał im się pomysł błąkania się tam i bycia ciągle ostrzeliwanym przez Indian. Więc dranie zaciągnęli mnie do najbliższego portu, ponieważ nasz lekarz zginął podczas walki z Holendrami, potrzebowali nowego.\nTak trafiłem do tego doktora, chcieli mnie przywrócić do przytomności na wystarczająco długo, by mnie torturować i dowiedzieć się, gdzie są kamienie. Wierzę, że później mnie rozkroiliby i nakarmiliby kraby moim soczystym mięsem.";
			link.l1 = "Nie mogę powiedzieć, że ich osądzam - próbowałeś oszukać swoich ludzi. Więc pytam ponownie, dlaczego mi o tym mówisz?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Te psy nie byli ludźmi, uwierz mi, teraz są wszyscy tam, gdzie im się należy - w piekle, ha-ha! W zamian za moją wolność i życie mogę podać dokładną lokalizację holenderskich skarbów.";
			link.l1 = "Nie, Bart, twoja zdrada całkowicie przekonała mnie o twojej podłości. Willemstad i zgodna z prawem kara czekają na ciebie. Bez układu.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "I czy mam uwierzyć, że te klejnoty naprawdę istnieją? Nieważne, i tak nic nie stracę... Umowa była początkiem tej historii i umowa będzie jej końcem. Akceptuję twoje warunki, Portugalczyku.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Traktuj to jako moją skromną wdzięczność. Eh, chciałbym wiedzieć, ile kosztuje skóra Bartolomeo Portugalczyka w błyszczących peso, ha! Rozumiem, że twoje cele były ściśle praktyczne, ale mimo to, dziękuję, kapitanie, za wszystko, ha-ha\nSkarb znajduje się na wyspie Turks, w dżungli niedaleko wybrzeża. Znajdź suche, krzywe drzewo, jest tam tylko jedno takie drzewo. Zakopałem skrzynię blisko niego. Więc nie zapomnij wziąć łopaty. Szczęśliwego polowania...";
			link.l1 = " Dobrze, będę o tym pamiętał, a ty możesz teraz wsiąść na szalupę i zniknąć z mojego statku. Żegnaj.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "Jeszcze jedna rzecz, kapitanie. Przypuszczam, że wciąż jest dużo dzikusów, ale to nie tylko ich powinieneś się obawiać. Vasquez nie był na 'Albatrossie', prawda? Krwawy Don jest zbyt sprytny... uważaj na siebie, dopóki nie zobaczysz go powieszonego lub z kulą w głowie.";
			link.l1 = "Dzięki za ostrzeżenie, Portugalczyku. A teraz łaskawie opuść już mój statek... nie wystawiaj mojej cierpliwości na próbę.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "O, a ktoż to jest! Kapitan "+pchar.name+" osobiście! Chcesz się napić?";
			link.l1 = "Wiesz, naprawdę cieszę się, że znów cię widzę. Ale być może byłem zbyt szorstki wobec ciebie na Martynice.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Cokolwiek, kapitanie! Co się stało, to się stało... Ale prawdę mówiąc, naprawdę dałem ci powód, by mnie odesłać... Ale hej, nie uwierzysz, kto jest dziś gościem w Phillipsburgu!";
			link.l1 = "Nie mów mi, że to jest...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "Nie, nie, kapitanie, to nie Portugalczycy. I to nie jakiś znowu ranny drań. To o wiele lepiej! To Hernando Vasquez... Sam Krwawy Don! Jest gościem lokalnego gubernatora od kilku ostatnich dni.";
			link.l1 = "Vasquez? Gość gubernatora? Teraz rozumiem. Hugo, powiedz mi więcej o tym, co się tu do diabła dzieje?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Cóż, wiem wiele... ale dzięki naszej podróży, znów jestem bankrutem. Może twoja potrzeba tej informacji jest warta kilku peso?";
			link.l1 = "Hugo, nadal jesteś wymuszaczem i łajdakiem! Mów, co masz na myśli, weź 5000 pesos tylko ze względu na naszą starą przyjaźń.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Jakoś mnie to nie dziwi. Masz tu 10000 pesos i lepiej miej nadzieję, że twoje informacje są warte tyle pieniędzy!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "Mam dla ciebie lepszą propozycję. Co powiesz na dołączenie do mojej załogi? Sądzę, że masz talent do zawierania i znajdowania opłacalnych interesów, więc jeśli masz dość udawania dzielnego wojownika - jesteś więcej niż mile widziany na stanowisku mojego skarbnika.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "Nie, kapitanie, to tak nie zadziała! Na pewno zgarnąłeś dużą sumę z tym przeklętym Portugalczykiem. Więc uznaj to za moją część, nie bądź taki chciwy. 15000 monet i ani peso mniej!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Do diabła z tobą, bierz je!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Cóż, a mówią, że chciwość jest dobra... Czy to nie za dużo dla ciebie, co?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "To jest dopiero nagroda dla mnie! ... Słuchaj, Vasquez płynął ze mną na tym samym statku, ale podczas gdy ja czyściłem pokłady jako zapłatę za podróż, on odpoczywał w kabinie, więc dzięki Bogu rzadko się widywaliśmy i nie rozpoznał mnie. Ale natychmiast zacząłem śledzić tego diabła... Zdarzyła się z nim ciekawa historia.";
			link.l1 = "Śmiało! Co on robi w pałacu gubernatora?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Nie wiem wiele, ale garnizon został zaalarmowany na kilka dni po jego przybyciu, a ogromny okręt wojenny nagle podniósł kotwicę i odpłynął w wielkim pośpiechu, według mnie na północny zachód. Całe miasto było pogrążone w domysłach i plotkach...";
			link.l1 = "A więc to był statek, który spotkałem! Intrygujące... Nie odbiegaj od tematu, Hugo, kontynuuj swoją opowieść, proszę.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Cóż, jak już mówiłem, statek zniknął, a Vasquez stał się swego rodzaju gościem naszego gubernatora Martina Thomasa. Czasami widuję go w mieście, zawsze w towarzystwie kilku żołnierzy. Nie wiem, czy to jego eskorta, czy konwój, ha-ha. Ale tylko ludzie w rezydencji mogliby ci powiedzieć więcej o Donie.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Być może masz rację. Ale mieliśmy umowę, pamiętasz? Nie baw się w bohatera, idź na mój statek i czekaj na mój powrót. Spróbuję porozmawiać z naszym gościnnym gubernatorem.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Cóż, to było interesujące. Naprawdę mi pomogłeś, Hugo. Pij swój rum, reszta cię nie dotyczy.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Jesteś poważny, kapitanie? Co z tobą nie tak? Przegoniłeś mnie, celując pistoletem w twarz, a teraz przychodzisz z takimi propozycjami?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Zapomnij o tym, nie byłem sobą i przepraszam, chciwość mnie opanowała, jak sądzę. Proszę, weź 10000 pesos i powiedz mi, co wiesz o Vasquezie, śpieszę się.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Może powinienem za to przeprosić. Jesteś żałosnym wojownikiem, ale dobrze sobie radzisz z monetami. Powtarzam swoją propozycję, co ty na to?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "Cóż mogę rzec... Zgadzam się, ale tylko po tym, jak dostanę swoją dolę, kapitanie. Dziesięć procent, pamiętasz? Otrzymałeś dwa tysiące za tego łajdaka, więc jeśli prosisz mnie, abym dołączył do twojej załogi, lepiej zacznij od wymazania swoich długów. Dziesięć procent i żadnych sprzeciwów!";
			link.l1 = "Jesteś takim oszustem, Hugo. Nie mam teraz tyle przy sobie, ale wrócę wkrótce. Zostań tutaj.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "Mam nadzieję, że spełnisz moje oczekiwania z tym swoim zmysłem do interesów, ha! Weź swoją dolę!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "To twoja decyzja, kapitanie. Zostanę tu na chwilę. Wróć, jeśli zmienisz zdanie.";
			link.l1 = "Dobrze, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Czy zmieniłeś zdanie, kapitanie? Czekam zatem na moje pieniądze.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Weź swoje monety, łotrze ha-ha!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Nie mam jeszcze takiej sumy.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Dzień dobry, kapitanie. Chcesz coś?";
			link.l1 = "Nie, nie, ja tylko czekam, kiedy pan Thomas będzie wolny? Czekam na audiencję... tak. Powiedz mi, czy jego Ekscelencja naprawdę uważa słynnego pirata Hernando Vasqueza za swojego przyjaciela?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Nie martw się, mynheer, powinien być wolny lada moment, a oczywiście, że nie, mynheer! Ten bandyta poddał się władzom, ale jakimś cudem nie został powieszony. Może kupił sobie życie, zdradzając swoich dawnych wspólników w zbrodni... Nie jestem pewien. Siedzi tu uwięziony od kilku dni... To był koszmar, mynheer! Ta bestia w ludzkiej postaci mieszkała w naszej rezydencji!";
			link.l1 = "Rzeczywiście koszmar! Cóż ta bestia mogłaby powiedzieć panu Thomasowi, aby uniknąć szubienicy? Nawet sobie nie wyobrażam!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Ja też nie wiem, ale mogę ci w tajemnicy powiedzieć, że wszyscy służący cieszyli się, gdy jego Ekscelencja pozbył się takiego gościa...";
			link.l1 = "Pozbył się go? Czy w końcu dostał to, na co zasłużył?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Nie do końca. Jeszcze nie. Kilka dni temu został zabrany na wojskowy bryg, który odpłynął do Willemstad. Widzisz, mynheer Thomas stracił zainteresowanie łajdakiem, wydaje się, że próbował go oszukać. Mówią też, że złapano jego byłego kapitana - Bartolomeo Portugalczyka! Pomyśl tylko o tym! Wygląda na to, że Kompania chce ich powiesić razem. Ptaki mówią, że proces odbędzie za miesiąc, ale po co czekać tak długo?";
			link.l1 = "Portugalczycy?! Hm... dziękuję za towarzystwo, przyjacielu... wydaje się, że pan Thomas jest teraz wolny, więc się oddalę.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Teraz jesteście martwi... obaj!";
			link.l1 = "O kurwa! Jeszcze się przekonamy!";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Teraz to ktoś, kogo się nie spodziewałem zobaczyć, kapitanie! Ale to nie wygląda jak przyjacielska wizyta, cała ta krew, hałas i strzelanina, czy to jakaś celebracja z fajerwerkami, co?";
				link.l1 = "Przestań rzucać swoje nikczemne dowcipy, Portugalczyku. Po prostu nie podoba mi się, jak wykorzystałeś swoją wolność, którą ode mnie wykupiłeś. Włożyłem zbyt wiele wysiłku, aby uratować twój żałosny tyłek, by pozwolić ci zostać tak głupio schwytanym zaraz po naszym rozstaniu!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Cóż, byłem znudzony! Więc przyszedłem tutaj, aby cię odwiedzić. Czy jest ci tu wygodnie, przyjacielu!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Ostrożnie, przyjacielu! Eh, szkoda, że nie mogę ci pomóc!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Więc szlachetność czasem nie jest zależna od monet, co? Ha... UWAŻAJ, ZA TOBĄ!";
			link.l1 = "Agh!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "Więc szlachetność czasem nie zależy od monet, co? Ha... UWAGA, ZA TOBĄ!";
			link.l1 = "Agh!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "Ostrzegałem cię, że ten facet to definicja kłopotów!";
			link.l1 = "Prawie udało mu się mnie zastrzelić w plecy! Jak on się przedostał?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "Widziałem, że miał wytrych, wygląda na to, że ktoś mu go dał... zawsze miał kontakty w niższych warstwach. Cóż, kapitanie, wierzę, że powinniśmy opuścić to miejsce, zgadzasz się?";
			link.l1 = "Co ty nie powiesz?! Dobrze, pośpieszmy się, zanim dotrze tu cały garnizon. Zaraz złamię twoją kłódkę...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Wiesz, kapitanie, to świeże powietrze... zaczynasz je doceniać dopiero po spędzeniu kilku tygodni w lochu zaraz po tym, jak łódź twojego statku została znaleziona przez lokalny patrol. Przypuszczam, że wciąż jestem ci winny za moje ocalenie.";
			link.l1 = "Nie trzeba, Portugalczyku. Nie jestem honorowym rycerzem, ja po prostu... Robię to, co uważam za słuszne i co trzeba zrobić.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, a to jest doskonała cecha! Ale nalegam, weź to... to jedyna rzecz, którą udało mi się ukryć w więzieniu... Tak, dobrze zrozumiałeś. To mój talizman. Zawsze przynosił mi szczęście na morzu. Jesteś dobrym żeglarzem i ty lub twój nawigator będziecie mogli go użyć, jestem tego pewien.";
			link.l1 = "Tak, a ty miałeś tyle szczęścia, że z tym talizmanem trafiłeś prosto w ręce Holendrów.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Ej! Wciąż żyję, prawda? I żebyś wiedział, nie jestem już w więzieniu. Weź to, kapitanie, czas, by talizman ci służył. I jeszcze raz dziękuję!";
			link.l1 = "Żegnaj zatem, Portugalczyku. I, proszę, trzymaj się z dala od szubienicy! Dla dobra mojej ciężkiej pracy, ha-ha!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("Otrzymałeś talizman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
