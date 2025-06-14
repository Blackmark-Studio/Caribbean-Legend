#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("Pierwsza wizyta w tawernie " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Podniesiono w mieście alarm, i wszyscy cię szukają. Gdybym był tobą, nie zostawałbym tutaj.","Wszyscy strażnicy miasta przeczesują miasto, szukając właśnie ciebie. Nie jestem głupcem i nie zamierzam z tobą rozmawiać!","Uciekaj, "+GetSexPhrase("kolego","dziewczyno")+", zanim żołnierze zamienią cie w mielone mięso..."),LinkRandPhrase("Czego chcesz, "+GetSexPhrase("łotrze","smrodzie")+"?! Strażnicy cie wyczuli, nie uciekniesz daleko"+GetSexPhrase(", brudny piracie!","")+"","Morderca! natychmiast opuść mój lokal! Straż!","Nie boję się ciebie, "+GetSexPhrase("łotrze","szczurze")+"! Wkrótce zostaniesz powieszony w naszym forcie, daleko nie uciekniesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm to dla mnie żaden problem...","Mnie się nie da złapiać."),RandPhraseSimple("Zamknij swoją gębę, "+GetWorkTypeOfMan(npchar,"")+", albo wyrwę ci język!","Heh, "+GetWorkTypeOfMan(npchar,"")+", ty tylko w gębie mocny jesteś - aby złapać piratów! Powiem ci więc krótko, przyjacielu: siedź cicho a nie umrzesz..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("To ty, łajdaku! Myślisz, że rum tu lejemy dla takich jak ty? Ależ skąd! Chłopcy! Do broni! Zabijcie tego łotra!","Chcesz się napić, piracie? Ha! Chyba w snach! Teraz pokażemy ci, co i jak! Chłopcy, do broni!");
				link.l1 = RandPhraseSimple("He? Co?","Chwila!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Drogi Panie, szukam pracy. Macie jakieś zajęcie?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "Wykonałem twoje zadanie. Szalupa z rumem została dostarczona do zatoki Le Francois i przekazana twoim ludziom.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Czegoś potrzeba, Panie?";
				Link.l1 = "Witaj karczmarzu, pilnie potrzebuję załogi do mojego statku. Czy możesz mi w tym pomóc?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Witam ponownie szanownego Pana. Co tym razem?";
				Link.l1 = ""+npchar.name+", Zdaję sobie sprawę, że przeszkadzam, ale mam jeszcze jedno pytanie. Potrzebuję nawigatora - masz jakieś pomysły, gdzie mogę go znaleźć?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "Co Monsieur sobie życzy?";
				Link.l1 = "Miałbym nadzieję, że odpowiesz na kilka pytań.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Chciałbym wynająć pokój.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Cieszę się, że Pana widzę! Jak mogę służyć? Rum, brandy, a może szkocka whisky?";
				Link.l1 = "Chciałbym butelkę waszego najlepszego francuskiego wina i klucz do pokoju.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Już zapłaciłeś, Panie, twój pokój jest na górze.";
				Link.l1 = "Dzięki.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "Jak mogę służyć, Kapitanie? Pewnie chcesz się napić po tym, co się stało.";
				Link.l1 = "To może poczekać. Właściwie chciałbym omówić, co się stało.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Proszę wybaczyć, "+GetAddress_Form(NPChar)+", ale dziś nie mogę zaoferować ani kropli alkoholu.";
				Link.l1 = "Co takiego? Co to za karczma, w której nie można dostać nawet kropli rumu? Czyżby ominęło mnie"+GetSexPhrase("","a")+" wielkie święto, które wyczerpało wasze zapasy?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Witam w mojej skromnej karczmie '"+XI_ConvertString(NPChar.City+"TavernName")+"'. Cieszę się, że cię widzę, Panie!","Do usług, Panie! W naszej karczmie '"+XI_ConvertString(NPChar.City+"TavernName")+"' zawsze cieszymy się z powitania nowych gości.","Pierwszy raz tutaj, Panie? Prosze się nie wachać, tu w '"+XI_ConvertString(NPChar.City+"TavernName")+"' zawsze można poczuć się jak w domu!"),LinkRandPhrase("Zapraszam, Kapitanie. Nie rozpoznaję cię, więc to musi być twoja pierwsza wizyta w '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Nigdy wcześniej cię nie spotkałem, Panie. Prosze pozwolić, że się przedstawie. Nazywam się "+GetFullName(npchar)+", jestem właścicielem karczmy '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Cieszę się, że mogę powitać naszego nowego gościa, Monsieur Kapitanie! W mojej karczmie '"+XI_ConvertString(NPChar.City+"TavernName")+"' pierwszy drink zawsze na koszt firmy! Jestem właścicielem tego miejsca, nazywam się "+GetFullName(npchar)+"."),LinkRandPhrase("Señor Kapitanie! Witamy w karczmie '"+XI_ConvertString(NPChar.City+"TavernName")+"'!","Oh, cóż za błyszczący hidalgo odwiedził naszą karczme '"+XI_ConvertString(NPChar.City+"TavernName")+"'! Czy to Pana pierwszy raz tutaj?","Dzień dobry, Panie! Jestem "+GetFullName(npchar)+", skromny właściciel '"+XI_ConvertString(NPChar.City+"TavernName")+"', ciesze się, że moge tu Pana ugościć!"),LinkRandPhrase("Witaj, Panie kapitanie. Jestem właścicielem karczmy '"+XI_ConvertString(NPChar.City+"TavernName")+"'. Pierwszy raz u nas?","Dzień dobry, Panie. Witamy w karczmie '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Bardzo dobrze cie widzieć, Mynheer kapitanie! Nasza karczma '"+XI_ConvertString(NPChar.City+"TavernName")+"' wita cię z otwartymi ramionami! Rum, wino, a może skusiłbym Pana na coś innego? Mamy tu nowy, psotny i mały holenderski spirytus zwany ginem!"));
				Link.l1 = LinkRandPhrase("Przytulne miejsce tu macie... Pozwoli Pan, że się przedstawię - "+GetFullName(pchar)+", miło poznać.",""+GetFullName(pchar)+", miło mi poznać. Więc, co może mi Pan zaoferować?","Nazywam się "+GetFullName(pchar)+" i jestem nowy w tym porcie. Powiedz mi, z czego ta karczma jest najbardziej znana?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Hej, Rumba! Wróciłaś z podróży, czy wyruszasz w nową?";
					link.l1 = "Witaj, "+npchar.name+". Po prostu postanowiłam wpaść.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "No więc, kapitanie, przyniosłeś mi "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Tak, mam. Oto one...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Nie, jeszcze nie...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Co też "+GetSexPhrase("panu","pani")+"potrzeba?";
						link.l1 = "Butelka rumu dla mojego kumpla przy tamtym stole.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, szanowni goście! Hej, ty - przesuń się i zrób miejsce dla dzielnego kapitana! I to szybko, zanim cię wyrzucę, haha!","Bóg się nad nami ulitował! To przecież "+GetFullName(pchar)+"! Właśnie dostałem nową dostawę najwyborzystszych win, proszę wejdź!","Oh, "+GetAddress_Form(NPChar)+", masz jakieś kłopoty? Pozwól, że cię czymś poczęstuję. Ta butelka jest za darmo. zaufaj mi, to najlepsze wino w okolicy..."),LinkRandPhrase("Oh, to przecież Kapitan "+GetFullName(pchar)+"! Hej, ty! Okazuj szacunek dobremu kapitanowi! To nie jest stodoła! Przepraszam cię, Kapitanie, ich matki najwyraźniej nie nauczyły ich manier.","Prosze prosze, zjawił się "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Czeka nas długa noc, haha! Dziewczyny, lepiej miejcie na sobie swoje najlepsze sukienki!","Dobry wieczór, "+GetFullName(pchar)+", Cieszę się, że cię widzę! Proszę Pana, mam prośbę. Właśnie kupiłem nowe stoły, więc proszę, dziś wieczorem bez walk."),LinkRandPhrase("Witaj, Kapitanie. Czuj się jak u siebie w domu, ale pamiętaj, że nawet sam Kapitan Sharp zachowuje maniery w moim lokalu.","O-ho-ho! Któż to jest? To "+GetFullName(pchar)+" sam we własnej sobie! A właśnie zaczynaliśmy się nudzić bez ciebie! Co powiesz na to, abyś rozbawił chłopaków jakąś przygodą, podczas gdy ja otworzę nową beczkę rumu, Kapitanie?","O-ho-ho! To "+GetFullName(pchar)+" sam we własnej osobie! Mam nadzieję, że nie zamierzasz znów zabierać moich klientów na otwarte morze opowieściami o swoich wielkich przygodach?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Ten stary piernik zawsze ucieszy się na twój widok w swoim przybytku! Proszę usiądź Panie, a dziewczyny się tobą zajmą!","Proszę rozgość się, Kapitanie! Zawsze się cieszę, kiedy mogę przywitać mego ulubionego gościa. Co podać?","Cieszę się, że znowu cię widzę, "+GetFullName(pchar)+"! Chciałbyś stolik dla siebie? Czy wolisz usiąść przy barze?"),LinkRandPhrase("Dzień dobry, Kapitanie. W powietrzu czuć lekki chłodek, pozwól, że zaproponuję Ci doskonałe grzane wino, które właśnie zrobiłem, na koszt firmy!","Witaj, "+GetFullName(pchar)+"! Cieszę się, że znów przyszedłeś w odwiedziny. Co byś chciał tym razem?","Witam ponownie, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Cieszę się, że odwiedzasz mój skromny lokal! Robimy wszystko, co w naszej mocy, aby zadowolić naszych stałych bywalców."),LinkRandPhrase("Kapitanie! Witamy, witamy! Mam dla Ciebie coś wyjątkowego, d'Anjou godne samego Króla Ludwika! Specjalnie dla Ciebie zachowałem!",""+GetFullName(pchar)+"! Jak miło, że wpadłeś. Czy mam przegonić wszystkie te morskie szczury, czy wolisz, żeby zostały? Uwierz mi, z przyjemnością opróżniłbym dla ciebie całą karczme!","Mój Boże, toż to Kapitan "+GetFullName(pchar)+"! Hej, zalotnice - przynieście najlepszą serwetę na stół kapitana!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("O, widzę, że pamięć o mnie nie najgorsza... Do kroćset, napełnij mój kielich, podczas gdy rozejrzę się dookoła...","Uspokój się, kolego, dzisiaj jestem w dobrym humorze. Zacznijmy od rumu, co ty na to?..."),RandPhraseSimple("Oho... czyżbyś nie był zadowolony z mojej obecności? Mam nadzieję, że źle cię usłyszałem, ha!","Ahoj. Mam nadzieję, że twoje wino jest lepsze niż twoje powitanie? Inaczej mogę się zirytować, wiesz...")),RandPhraseSimple(RandPhraseSimple("Zawsze z miłą chęcią cie odbiedze, kolego. Masz coś, żeby rozgrzać starego wilka morskiego?","Ahoj kumplu, twoja knajpa staje się lepsza z każdym dniem! Odwiedziny to zawsze przyjemność..."),RandPhraseSimple("Nie zapomniałeś o starym wędrowcu? Jestem zaszczycony, przyjacielu.","Dobrze jest znowu widzieć starego przyjaciela... Czy został ci jeszcze jakiś rum?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Słucham, Kapitanie.","Moja karczma '"+XI_ConvertString(NPChar.City+"TavernName")+"' do usług, Kapitanie!","Słucham, Kapitanie! Czego dziś sobie życzysz?");
				Link.l1 = "Czy są na wyspie jacyś młodzi i zdolni chłopcy, którzy chętnie spróbują swojego szczęścia na morzu?";
				Link.l1.go = "crew hire";
				Link.l2 = "Mam nadzieję, że odpowiesz mi na kilka pytań.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Chciałbym porozmawiać o sprawach finansowych.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Czy możesz mi coś powiedzieć o ostatnim rabunku w kościele?","Co wiesz o niedawnym rabunku w kościele?","Słyszałeś coś o niedawnym rabunku w kościele?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Ludzie mówią, że wiesz prawie wszystko o tej kolonii. Chciałbym nabyć "+pchar.GenQuest.Device.Shipyarder.Type+", a powiedziano mi, że było to sprzedawane w waszym mieście. Cóż, ktoś to sprzedawał na rynku. Czy możesz mi coś o tym powiedzieć?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Szukam krętacza o imieniu "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Gdzie mogę go znaleźć?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Witaj, "+npchar.name+". Muszę znaleźć Jacoba van Berga - gdzie on jest? Nie widzę go w twojej karczmie...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Witaj, "+npchar.name+". Szukam pewnego caballero o imieniu Fernando Rodriguez. Czy pokazywał się w twoim mieście?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Przyszedłem odebrać moje wygrane, które bezpiecznie przechowywałeś u siebie."+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Zastanawiałem się, gdzie mogę znaleźć człowieka o imieniu "+pchar.GenQuest.Marginpassenger.q2Name+"? Mieszka gdzieś tu w mieście.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("Masz wolny pokój, kolego?","Czy masz wolny pokój, chciałbym tu zostać na jakiś czas.");
					link.l3.go = "room";
				}
				Link.l4 = "Niestety, ale pora na mnie, "+NPChar.name+". Do zobaczenia.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ach tak, wejdź, wejdź. Zawsze jesteś tu mile widziana.";
			link.l1 = "Dziękuję. Dobrze było cię zobaczyć. Do widzenia.";
			link.l1.go = "exit";
			Link.l2 = "Przydałoby mi się kilka nowych rąk na pokładzie. Tylko upewnij się, że są zdolni, dobrze?";
			Link.l2.go = "crew hire";
			link.l3 = "Chciałabym odpocząć na solidnym gruncie i zebrać myśli, nie gdy moja matka hasa po domu.";
			link.l3.go = "Helen_room";
			Link.l4 = "Mogę ci zadać pytanie? ";
			Link.l4.go = "quests";
			link.l5 = " Mam z tobą sprawę do omówienia, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Czego sobie życzysz, "+GetSexPhrase("Panie","Pani")+"?";
				link.l1 = "Butelka rumu dla mojego kompana przy tamtym stole.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Słucham, Kapitanie.","Co mogę ci zaoferować, Kapitanie?","Więc Kapitanie, co podać?");
			Link.l1 = "Potrzebuję załogi, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", porozmawiajmy jeśli nie masz nic przeciwko...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Chciałbym porozmawiać o sprawach finansowych.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Czy możesz mi coś powiedzieć o niedawnym rabunku w kościele?","Co wiesz o niedawnym rabunku w kościele?","Słyszałeś coś o niedawnym rabunku w kościele?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Ludzie mówią, że wiesz prawie wszystko w tych stronach. Pragne nabyć coś takiego jak "+pchar.GenQuest.Device.Shipyarder.Type+", wiem, że sprzedawano to w waszym mieście, i to dosyć niedawno. Możesz mi o tym coś powiedzieć?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Opowiedz mi o gościu, który nazywa się "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Gdzie mogę go znaleźć?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Witaj, "+npchar.name+". Muszę znaleźć Jacoba van Berga - gdzie on jest? Nie widzę go w twojej tawernie...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Cześć, "+npchar.name+". Szukam pewnego caballero o imieniu Fernando Rodriguez. Był tu ostatnio?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Przyszedłem odebrać moje wygrane, które są u ciebie bezpieczne."+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Zastanawiałem się, gdzie mogę znaleźć człowieka o imieniu "+pchar.GenQuest.Marginpassenger.q2Name+"? Wiem, że powinien gdzieś tu w mieście mieszkać.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("Masz wolny pokój, kolego?","Czy masz wolny pokój, chciałbym tu zostać na jakiś czas.");
				link.l3.go = "room";
			}
			Link.l4 = "Chyba wrócę później.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "A co by ci marynarze byli potrzebni, Kapitanie? Nie widzę w porcie twojego statku.";
				link.l1 = RandPhraseSimple("Faktycznie... Zawinąłem nie tam gdzie trzeba.","Wybacz... Widocznie pomyliłem porty.");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Zwykle jest wielu chętnych do zostania marynarzami, ale teraz jest za późno - zaczną pojawiać się dopiero nad ranem. Może chciałbyś wynająć pokój i na nich poczekać?";
				link.l1 = "W porządku. Czy masz wolne pokoje?";
				link.l1.go = "room";
				link.l2 = "Nie jestem teraz zainteresowany pokojem. Do zobaczenia.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Myślisz, że obsługujemy tu poszukiwanych przestępców? Bądź wdzięczny, że nie wołam straży.";
					link.l1 = "Dzięki.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Kapitanie, dziś w karczmie ani żywej duszy. Wszyscy chętni poszli z kapitanem Blackwoodem.";
						link.l1 = "To szkoda!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ach, przepraszam Kapitanie, zjawiłeś trochę za późno. Wszyscy chłopcy, którzy chcieli, właśnie wypłynęli z dzielnym kapitanem "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "A to szkoda!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Kapitanie, ludzie mówią, że jesteś niezwykłym skąpcem. Nie mamy tu nikogo, kto chciałby dołączyć do twojej załogi.";
									link.l1 = "Rozumiem...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Zamieniam się w słuch.";
			//link.l1 = "Szukam pracy. Możesz mi pomóc?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Czy są jakieś najnowsze wiadomości, o których możesz mi powiedzieć?","Co się dzieje w tych stronach?","Co nowego na lądzie?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Jestem tu w innej sprawie.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Czy wiesz, gdzie mogę znaleźć "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Czy mógłbyś mi powiedzieć, gdzie mogę poszukać "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Przyszedłem na zaproszenie twojego syna."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "A więc, widziałeś może "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Czy możesz mi powiedzieć, gdzie powinienem szukać "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Czy wiesz, gdzie mogę znaleźć kapitana patrolu "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Czy widziałeś "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Czy wiesz coś o kapitanie patrolu "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Czy mógłbyś mi powiedzieć, gdzie znajdę człowieka o imieniu "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Niedaleko stąd znalazłem przypadkowo jakieś dokumenty statku....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Słuchaj, szukam swojego starego przyjaciela, "+pchar.GenQuest.FindFugitive.Name+" to jego imię. Jeden z kapitanów powiedział mi, że zmierzał do twojej kolonii. Spotkałeś go może przypadkiem?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Nic, dziękuję.";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Co powiedziałeś?"+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Nigdy o nim nie słyszałem.","Czy jesteś pewien, że on pochodzi z naszego miasta? Nigdy nie słyszałem o takiej osobie.","Nie było nikogo takiego w naszej małej kolonii. Nigdy o nim nie słyszałem przez cały mój czas tutaj.");
					link.l1 = "Czy jesteś pewien?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "w kościele";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "w stoczni";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "w kościele";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "lichwiarza";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "okoliczny sklep";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Sprawdź "+pchar.GenQuest.Hold_GenQuest.foundStr+", często można go tam znaleźć.";
					link.l1 = "Dziękuję, właśnie tak zrobię.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("Co powiedziałeś?"+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Nigdy o nim nie słyszałem. Jesteś pewien, że pochodzi z naszej osady? Nigdy nie słyszałem o takiej osobie.","He-he... Cóż, teraz tylko Pan Bóg wie, gdzie go szukać - w piekle czy w niebie. Zmarł ponad rok temu, ale ludzie nadal o nim pytają... Nie ma spokoju dla biedaka..."),RandPhraseSimple("Nie znajdziesz go tam - przynajmniej nie wśród żywych. Zmarł nie tak dawno - żółta febra... Niech spoczywa w pokoju... Co to był za twardy mężczyzna! Kiedy był młody, był wielkim poszukiwaczem przygód! Ale kiedy śmierć idzie za tobą, niewiele możesz zrobić...","Och, czy tęsknisz za nim? Dawno opuścił te miejsca. Nikt nie wie, dokąd poszedł - może do kolonii północnoamerykańskich, może wrócił do domu, do Europy. Po prostu zebrał swoje rzeczy i zniknął."),"Oh, czy szukasz tego "+pchar.GenQuest.Hold_GenQuest.Name+" kto się wzbogacił i kupił sobie dom w Nowej Anglii? Wiesz, były czasy, kiedy sprzedałem mu rum na kredyt - nadal jest mi dłużny. Ludzie są tacy niewdzięczni, wiesz.");
					link.l1 = "Rozumiem. Cóż, i tak dziękuje.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Cóż, gdzie indziej go szukać, jeśli nie w karczmie? Często tam bywa - zanurza swoje grzechy w winie, he-he. Wróć za chwilę - jeśli się pojawi, powiem mu, żeby na ciebie poczekał.";	
					link.l1 = "Dziękuję, zrobię to.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Jak mogę nie być pewien, jeśli znam tutaj wszystkich osobiście. To nie pierwszy rok, kiedy prowadzę tutaj tawernę."+"Widziałem ich wszystkich we wszystkich możliwych stanach. Czasami żona przychodziła odebrać swojego męża, czasem wychodzili sami, a czasami musiałem ich wyrzucić. 'Czy jestem pewien?!' Oczywiście, że tak!";
			link.l1 = "Cóż, dzięki i tak...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Często tu bywa, ale teraz go nie ma. Wróć od czasu do czasu - powiem mu, żeby tu na ciebie zaczekał, jeśli się pojawi.","Często tu bywa. Jeśli wrócisz później, to na pewno go znajdziesz.","Wróć od czasu do czasu - często tu zagląda. Powiem mu, że go szukałeś.");
			link.l1 = "Dziękuję, wrócę później...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "On już tu przybył, więc powinien być gdzieś w pobliżu...";
			link.l1 = "Dzięki.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Czy jest taki człowiek, który go nie zna? Cała osada o nim mówi już od kilku dni.";
			link.l1 = "Powiesz mi coś więcej?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Trochę, kapitan został stracony, to samo można powiedzieć o niektórych członkach jego załogi. Reszta została rozproszona po Karaibach, pozbawiona rangi i stanowiska... Za co? Według sędziego, zatopił pirata podczas patrolu i ukrył dla siebie łup"+"Problem tylko jest taki, że ani właściciel tego statku, ani towarów nie zostali odnalezieni... przeszukiwali lokalne zatoki i przystanie, ale na próżno.";
			link.l1 = "Co, żaden z człownków załogi nie ujawnił lokalizacji skrytki?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Żaden z nich! Nawet w trakcie tortur! Nadal nie mogę zrozumieć, dlaczego gubernator tak ochoczo uwierzył w te oszczerstwa. Kapitan "+pchar.GenQuest.CaptainComission.Name+" cieszył się dobrą reputacją, a jego załoga była na tyle dobrze wyszkolona i zdyscyplinowana, że każdy admirał mu zazdrościł.";
			link.l1 = "A gdzie powinienem szukać ocalałych członków załogi?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Tego nie wiem - rozproszyli się po czterech wiatrach... Chociaż... jeden z nich nadal jest, ale wątpię, czy dowiesz się od niego wiele. Był mocno wstrząśnięty. Wiesz, służył jako artylerzysta pod "+pchar.GenQuest.CaptainComission.Name+". Znaleziono go nieprzytomnego w zatoce dwa dni po tym wypadku. Najpierw został wysłany do szpitala i traktowany jak bohater, ale kiedy wszystko zaczeło stawać się jasne, to wrzucili go do lochu i próbowali przesłuchać. Potem jednak zadecydowali, że wpierw powinien zostać wyleczony.";
			link.l1 = "Jest tu teraz?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Tak, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" to jego imię. Przychodzi od czasu do czasu, wydaje na rum grosze, które zarabia żebrając. Biedna z niego dusza. Jeśli go zobaczę, powiem mu, żeby tu na ciebie poczekał.";
			link.l1 = "Dziękuję, wrócę później.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Czy go znam? Oczywiście, że tak. A po co ci on potrzebny?";
			link.l1 = "Mam z nim interesy...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", powinieneś być ostrożny z tymi 'interesami'. "+pchar.GenQuest.CaptainComission.Name+" został zatrzymany pod zarzutem piractwa, a ludzie gubernatora obecnie przeszukują wyspę w poszukiwaniu jego wspólników.";
			link.l1 = "Co ty gadasz! A co on zrobił?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Nie wiem, czy to prawda, czy nie, ale mówią, że schował konfiskowany ładunek z mijającego pirackiego statku i nie oddał go. I nadal nikt nie znalazł ani tego pirata, ani ładunku. Nadal nie mogę zrozumieć, dlaczego gubernator tak chętnie uwierzył w te oszczerstwa. Kapitan "+pchar.GenQuest.CaptainComission.CapName+"  miał przyzwoitą reputację, i był świetnym żołnierzem, możesz mi zaufać, "+GetAddress_Form(pchar)+".";
			link.l1 = "Cóż, dzięki za ostrzeżenie. Do zobaczenia.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "A po co ci ona potrzebna?";
			link.l1 = "Mam z nią interesy...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Połowa mężczyzn w naszej osadzie zdaje się mieć z nią jakieś interesy. Gdyby nasze kobiety ją złapały, wyrzuciłyby ją za bramy miasta, nagą.";
			link.l1 = "Cóż... "+GetSexPhrase("Wygląda na to, że trafiłem na długą kolejkę. No nic, jeśli ktoś inny przyjdzie jej szukać, powiedz im, żeby stali za mną w kolejce.","Rozumiem")+"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Często tu bywa - zazwyczaj przychodzi w poszukiwaniu pracy, ale teraz go tu nie ma. Wróć od czasu do czasu - powiem mu, żeby tu na ciebie poczekał, jeśli się pojawi.";
			link.l1 = "Dziękuję, wrócę później...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ach, więc to ty jesteś "+GetSexPhrase("tym kapitanem, który przywiózł","tą dziewczyną, która przywiozła")+" mojego rozrzutnego syna z jego panną młodą?";
				link.l1 = "Tak, to ja.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, jest i "+GetSexPhrase("nasz dobroczyńca",", nasza dobroczyńca")+". Oczekujesz nagrody, rozumiem?";
				link.l1 = "Cóż, obejdzie się bez nagrody, wystarczą mi Twoje podziękowania.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Bardzo jestem wdzięczny, że nie porzuciłeś mojego syna w trudnej sytuacji i pomogłeś mu znaleźć wyjście z tej delikatnej sytuacji. Pozwól mi osobiście ci podziękować i proszę przyjmij ode mnie tę skromną sumę i prezent.";
			link.l1 = "Dziękuję. Pomoc młodej parze była moją przyjemnością.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Dzięki? Jakie dzięki?! Pół roku ten dureń błąkał się bez pracy - a patrz na niego, ma wystarczająco dużo czasu na romans! Kiedy byłem w jego wieku, już prowadziłem własny biznes! Pfft! Gubernator ma do wydania córkę - a ten idiota przywiózł do mojego domu jakąś dziewkę bez rodziny i ośmielił się prosić o moje błogosławieństwo!";
			link.l1 = "Chyba nie wierzysz w miłość od pierwszego wejrzenia?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Miłość? Miłość!? Czy ty sobie ze mnie drwisz, czy jesteś głupi? Wstyd ci nie jest pobłażać młodym w ich kaprysach i zachowywać się jak alfons! Nie tylko zabrałeś dziewczynę z jej domu, ale także zrujnowałeś życie mojego chłopca. Nie będe ci za to dziękować. Żegnaj.";
			link.l1 = "Ty zapluta świnio! Jak śmiesz tak do mnie mówić?! Masz szczęście, że są tu świadkowie, inaczej już byś leżał zakrwawiony na ziemi. Żegnam!";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Daj mi się przyjrzeć! Hmm... Ale przecież sam jesteś kapitanem. Myślę, że powinieneś porozmawiać o tym z naczelnikiem portu.";
				link.l1 = "Dziękuję za twoją radę.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Daj mi zobaczyć! O! Sądząc po imieniu, to należy do jednego z moich gości, dość szanowanego pana. Sam mogę przekazać te dokumenty właścicielowi. Dasz mi je?";
				link.l1 = "Nie wydaje mi się...";
				link.l1.go = "exit";
				link.l2 = "Weź je. Cieszę się, że mogłem służyć pomocą.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Nie obchodzi mnie, komu nalewam piwa, skoro pieniądze nie mają narodowości. Ale tobie na pewno nie pomogę, ponieważ przyszedłeś pod flagą "+NationNameGenitive(sti(pchar.nation))+".","Jestem tylko prostym właścicielem karczmy, ale współpraca z "+NationNameAblative(sti(pchar.nation))+" nie wydaje mi się zbyt kusząca.");
				link.l1 = RandPhraseSimple("No cóż, jak sobie życzysz...","Cóż, jak wolisz...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Zwykle mamy tu wielu pasażerów. Mimo to, nie sądzę, żeby choć jeden z nich zgodził się podróżować na twoim statku. Twoja zła reputacja cię poprzedza, tylko głupiec wszedłby na statek z takim łotrem.","Dość często podchodzą do mnie kupcy, którzy potrzebują eskorty. Jednak twoja zła reputacja cię poprzedza, i nie polecę cię nikomu. Dbam o swoją własną reputację, wiesz. Nikt nie chce zatrudniać wilka do strzeżenia swoich owiec.");
				link.l1 = RandPhraseSimple("Oj, naprawdę, nie powinieneś wierzyć we wszystkie plotki jakie słyszysz...","Rozumiem. Ciężko jest zmusić wszystkich do zamknięcia się.","Ludzie są dzisiaj po prostu zbyt delikatni...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "A gdzie jest twój statek? Zamierzasz nosić pasażerów na swoich plecach?";
				link.l1 = "Rzeczywiście, masz rację...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Mogę mieć dla ciebie robotę, jeśli nie boisz się podróżować do pirackich osad czy portów wrogich narodów. Szukasz czegoś konkretnego?";
			link.l1 = "To nie powinno być problemem. Myślę, że mogę zapewnić eskortę.";
			link.l1.go = "work_1";
			link.l2 = "Czy masz jacyś pasażerowie? Mogę ich zabrać, gdziekolwiek chcą, jeśli za to zapłacą.";
			link.l2.go = "work_2";
			link.l3 = "Nie, taka praca nie jest dla mnie. Dzięki.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Zazwyczaj nie pytają mnie o eskortę. Zapytaj kupców przy stołach - może potrzebują twoich usług.";
				link.l1 = "Dobrze, skoro tak mówisz.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Przykro mi, ale nie mam nikogo, kto chciałby podróżować z tobą.";
					link.l1 = "Widzę.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "Jest tu jeden facet, który właśnie wszedł - niedawno pytał o statek, który go przewiezie. Możesz z nim porozmawiać, jeśli chcesz.";
					link.l1 = RandPhraseSimple("Kim on jest? Może to łajdak? Albo, co gorsza, poszukiwany pirat?","A kim on jest? Czy będą z nim jakieś kłopoty?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Nie, nikt się o to dziś nie pytał. Może kiedy indziej.";
					link.l1 = RandPhraseSimple("Cóż, jak nie ma, to nie ma...","A to pech... cóż więc, do zobaczenia, w takim razie.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Dziś nikogo nie ma. Wróć za kilka dni.";
				link.l1 = "Dobrze.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Kto wie? Ty zapytałeś - Ja odpowiedziałem.","Cóż, to jest raczej sprawa dla ciebie do rozwiązania. Ja za nikogo nie poręczę.","Przychodzą tu ludzie różnego sortu. To jest karczma, Kapitanie, nie dwór gubernatora.");
			Link.l1 = "Dzięki, czas więc sie potargować.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Skąd mam wiedzieć? Zapytałeś - to Ja odpowiedziałem.","Porozmawiaj z nim i się dowiedz. Ja za nikogo nie poręczę.","To jest karczma, Kapitanie, nie dwór gubernatora. Tu znajdziesz kogokolwiek, bądź to honorowego typa, bądź też totalną szumowine.");
			Link.l1 = "Rozumiem. Spróbuje dowiedzieć się, kim jest ten człowiek...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Oczywiście, Helen. Jak długo zostajesz? A co, pokłóciłeś się ze starą Gladys?";
			if(!isDay())
			{
				link.l1 = "Tylko, aby przespać do rana. Jeśli teraz wrócę do domu, na pewno ją obudzę.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "Nie, nie, muszę tylko wypłynąć nocą, a nie chcę jej budzić.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Chcę się porządnie wyspać i nie spieszyć ze wstawaniem. Wezmę pokój na jeden dzień.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "Pokój jest zajęty, "+GetAddress_Form(NPChar)+", nie ma nic, co mogę dla ciebie zrobić.";
				link.l1 = "Cóż, wielka szkoda...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Pan Henri Thibaut wynajmuje obecnie pokój i zapłacił za miesiąc z góry, więc nic nie mogę dla ciebie zrobić, Kapitanie.";
				link.l1 = "Cóż, szkoda...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Pokój jest zajęty, "+GetAddress_Form(NPChar)+", nie mogę ci pomóc.";
				link.l1 = "Cóż, to rzeczywiście szkoda...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "Pokój jest zajęty, "+GetAddress_Form(NPChar)+", nie ma nic, co mogę dla ciebie zrobić.";
				link.l1 = "Cóż, to szkoda...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Niestety nie, kapitanie. Wszystkie pokoje zajęte przez Blackwooda i jego ludzi.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Ech, szkoda!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Wszystkie pokoje? Jest tu więcej niż jeden?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Chcesz wynająć pokój? Żaden problem. 100 peso i jest twój.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Oto twoje pieniądze.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... Chyba wrócę później...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "Pokój jest cały twój. Idź śmiało i zrelaksuj się.";
				link.l1 = "Dzięki, kumplu.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Chcesz wynająć pokój? Nie ma problemu. 100 peso i jest twój.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Tu są twoje pieniądze.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... Chyba wrócę później...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "Pokój jest cały twój. Idź śmiało i zrelaksuj się.";
					link.l1 = "Dzięki, kumplu.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Przepraszam kapitanie, niestety nie ma wolnego pokoju. Gość nie chce wyjść. I nadal mi nie zapłacił...";
				link.l1 = "Wygląda na to, że będe musiał spędzić noc na sali...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "W porządku. Porozmawiajmy o czymś innym.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "Więc wezwij straże. Co to niby za gość, który nie płaci pieniędzy i nie chce się przy tym wynieść...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "Jak długo zamierzasz tu zostać?";
			if(!isDay())
			{
				link.l1 = "Aż do rana.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Aż do nocy.";
				link.l1.go = "room_night";
				link.l2 = "Aż do następnego ranka.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			dialog.text = "To będzie cię kosztować 5 peso.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Umowa stoi. Proszę bardzo.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Za taką cene? Ty wynajmujesz królewskie komnaty czy jak? Wolę już sobie odpocząć tu w sali za darmo.","Ach, luksus spania w łóżku wydaje się być poza moimi obecnymi środkami. Chyba będę musiał spać tu na sali na ławce.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Nie teraz. Zmieńmy temat.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = "To będzie cię kosztować 10 peso.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Zgoda. Proszę bardzo.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Za taką cene? Wynajmujesz królewskie komnaty? Wolę się przespać tu w izbie za darmo.","Niestety, luksus spania na łóżku wydaje się być poza moimi obecnymi możliwościami. Chyba będę musiał spać tutaj w sali na ławce.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Nie teraz. Zmieńmy temat.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = "To będzie cię kosztować 5 peso.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Umowa stoi. Proszę bardzo.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Za taką cene? Chcesz mi wcisnąć, że wynajmujesz tu królewskie komnaty? Wolę zostać w gospodzie za darmo.","Niestety, luksus spania na łóżku wydaje się być poza moimi obecnymi możliwościami. Chyba będę musiał spać w sali na ławce.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Nie teraz. Zmieńmy temat.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "Chyba ci się coś pomyliło? Wynoś się stąd do diabła! Sala może i jest za friko, ale takiego zachowania tu nam nie potrzeba!";
				link.l1 = "Dobrze, dobrze, już wychodzę.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Ja ci się zaraz wyśpie na ławce! Wypad stąd, łobuzie! Sala może być dla wszystkich, ale są pewne granice! A już na pewno nie będe pozwalał ci tu spać, jak jakiemuś żebrakowi!";
				link.l1 = "W porządku, już wychodzę.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Przerwijcie te skandaliczne zachowanie w mojej karczmie natychmiast, albo zawołam straże!";
			link.l1 = "Dobrze, dobrze.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Zbyt wiele nie wiem... Lepiej zapytaj klientów.";
			link.l1 = "Rozumiem, dzięki.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Nie udzielamy usług na kredyt, "+GetSexPhrase("Panie","Panienko")+".";
			link.l1 = "Płacę dobrą monetą. Już nie akceptujesz złota czy srebra?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Przykro mi, "+GetSexPhrase("Panie","Panienko")+", ale twój przyjaciel miał dług, a ja myślałem...";
			link.l1 = "Mniej myśl i szybciej pracuj, kumplu. Teraz do rzeczy, ile mój dzielny przyjaciel jest ci winien?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "Jeśli jest prosty i płaci od razu"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", pan"+GetSexPhrase("ie","i")+"kapitanie, on także zastawił kilka ksiąg kościelnych - to wszystko, co miał przy sobie, co miało jakąś wartość.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Tu są twoje monety. Oddaj rękopisy. I ostrożnie z nimi - to nie jest księga sprośnych drzeworytów, ale Święta Księga!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Poczekaj chwileczkę... Wrócę z pieniędzmi";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "Jeśli nie jest prosty"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", panie"+GetSexPhrase("","")+" kapitanie.";
				link.l1 = "Spłacę jego dług i wezmę wszystko, co zostawił w zabezpieczenie.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Nie, Pani"+GetSexPhrase("e","enko")+", to nie zadziała w ten sposób.";
			link.l1 = "Co masz na myśli mówiąc - 'to nie zadziała'? Dług kapitana jest spłacony - on jest spokojny. Masz swoje pieniądze z powrotem - jesteś spokojny. Biorę jego zastaw - jestem spokojn"+GetSexPhrase("y","a")+". Wszyscy są spokojni - więc dlaczego 'to nie zadziała'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Ponieważ, Pan"+GetSexPhrase("ie","i")+"Kapita"+GetSexPhrase("nie","n")+", ja nie potrzebuję pieniędzy. Znam tego kapitana aż za dobrze, dlatego też nigdy sie nie spodziewałem, że zwróci mi należne i zabierze te rękopisy ode mnie.";
			link.l1 = "Co masz na myśli - nie potrzebujesz pieniędzy? Czyli planowałeś zatrzymać te książki od samego początku? Ale dlaczego, na miłość Boską?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "W imię Boga - dokładnie, dlatego, Pani"+GetSexPhrase("e","enko")+". Mój mały chłopiec był bardzo chory, dlatego ja i moja żona przysięgliśmy, że złożymy dar kościołowi, jeśli nasz Błogosławiony Pan i Zbawca wyleczy dziecię z gorączki. Miłosierdzie naszego Pana okazało się być nieskończone, mój chłopiec wyzdrowiał, przez co musieliśmy dotrzymać naszej obietnicy. I akurat wtedy, Kapitan "+PChar.GenQuest.ChurchQuest_1.CapFullName+" pojawił się i zastawił te kościelne księgi. Nie mogłem sobie pozwolić na zignorowanie mojej przysięgi, dlatego postanowiłem przekazać te książki proboszczowi naszej parafii.";
			link.l1 = "Cóż, to oczywiście jest jak najbardziej dobry uczynek, ale powinieneś również wiedzieć, że te książki tak naprawdę należą do innego księdza - a właściwie nie tylko księdza, ale biskupa i mojego duchowego pasterza. A on może się zezłościć, a nawet przekląć tych, którzy ośmieliby ofiarować skradzioną własność Kościoła. Chciałbym je od ciebie kupić i bezpiecznie zabrać do domu. Możesz ofiarować pieniądze swojej parafii, jestem pewien, że Bóg to doceni tak samo.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Pan"+GetSexPhrase("ie","i")+"... Pan"+GetSexPhrase("ie","i")+" kapita"+GetSexPhrase("nie","n")+"... Oczywiście, nie miałem pojęcia! Oddam je z powrotem i nie wymagam za to żadnych pieniędzy. Wystarczy, że wspomnisz o nas biskupowi - może nas pobłogosławić i uwolnić od naszej przysięgi...";
			link.l1 = "Oczywiście, twoja przysięga będzie uznana za dotrzymaną! Przecież zrezygnowałeś ze swojego zysku, aby zwrócić książki ich prawowitemu właścicielowi. Nie ma znaczenia, który to konkretne kościół, bo jest tylko jeden Bóg i jeden Święty Katolicki Kościół Apostolski, prawda? Dobrze, daj mi je, i powodzenia ci życzę...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nigdy o tym nie słyszałem... Co to właściwie jest? Nigdy w życiu nie spotkałem się z taką rzeczą.";
			link.l1 = "No cóż, to narzędzie stoczniowe, "+pchar.GenQuest.Device.Shipyarder.Describe+". Czy ktoś ci coś takiego proponował?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Tak, jeden dziwny typ rzeczywiście przyniósł mi to, lecz nie powiedział mi, co to jest, tylko próbował wymienić to na gorzałkę. Oczywiście, odmówiłem - nie potrzebowałem tej pierdoły.";
				link.l1 = "A jak on wyglądał i gdzie poszedł? Bardzo potrzebuję tego narzędzia.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nie, nikt nic nie przynosił poza pieniędzmi. Przykro mi, nie mogę ci pomóc. Zapytaj dookoła.";
				link.l1 = "Rozumiem. Cóż - czas zapytać dookoła!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Był tam niedawno, a teraz powinien być u swojego towarzysza - sklepikarza. Spróbuj poszukać go w sklepie - na pewno tam musi być.";
				link.l1 = "Dzięki! Bardzo mi pomogłeś!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Dzisiaj, wcześnie rano, wypłynął na swoim szkunerze na morze. Założę się, że teraz stoi na burcie, podziwiając widok. Jeśli go potrzebujesz, możesz spróbować go znaleźć na morzu lub poczekać, aż wróci za kilka dni...";
				link.l1 = "Dzięki! Chyba nie będę czekał - łatwiej mi będzie go znaleźć na morzu. Pozdrawiam!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Dlaczego krzyczysz? On czeka na ciebie już od dawna. Wypił już pełną kwartę rumu. Idź na górę do pokoju, tam go znajdziesz.";
			link.l1 = "O, rozumiem. Miejmy nadzieję, że wciąż jest na nogach.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Tak, znam tego pana. Powinien być gdzieś w mieście - właśnie niedawno widziałem go przechodzącego obok mojego okna.";
				link.l1 = "Dziękuję! Pójdę go szukać!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Tak, znam tego pana. Powinien być gdzieś w mieście - właśnie niedawno widziałem go przechodzącego obok mojego okna.";
					link.l1 = "Dziękuję! Pójdę go szukać!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Tak, teraz odwiedza nasze miasto. W tej chwili go tu nie ma - wypłynął na swojej brygandynie. Prawdopodobnie nie jest daleko stąd, na wodach naszej wyspy.";
					link.l1 = "Dzięki kumplu! Bardzo mi pomogłeś!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Nigdy o nim nie słyszałem. Nie, nic o tym człowieku nie wiem.";
				link.l1 = "Rozumiem... Cóż, poszukiwania trwają...";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Tak, oczywiście. Gratulacje, Kapitanie. Już wiem o twoim zwycięstwie. Oto twoje pieniądze.";
			link.l1 = "Dziękuję Ci, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Emmm, Pan, "+pchar.GenQuest.Marginpassenger.q2Name+" zmarł około "+LinkRandPhrase("miesiąc","trzy tygodnie","dwa miesiące")+" temu. "+LinkRandPhrase("Nagle poddał się gorączce","Został zadźgany przy bramach miasta, przez bandytów czy tych czerwonoskórych dzikusów","Został zastrzelony w pojedynku")+". Świeć Panie nad jego duszą...";
				link.l1 = "Cholera!.. I co ja mam zrobić z jego... No cóż... Dzięki za informację. Do zobaczenia, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Tak, powinien być gdzieś w mieście. Szukaj go na ulicach. Ale pamiętaj, że każdego dnia do południa jest w biurze gubernatora, a po dziewiątej wieczorem zamyka się w swoim domu.";
				link.l1 = "Dzięki! Pójdę go szukać...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Wygląda na to, że twój armator mówił prawdę. "+pchar.GenQuest.FindFugitive.Name+" rzeczywiście niedawno przybył do naszej osady. Szukaj go na ulicach w ciągu dnia - zazwyczaj marnuje tam swój czas.","Już mnie pytałeś o tego człowieka, i powiedziałem ci wszystko, co wiedziałem!","Żartujesz sobie ze mnie, czy rzeczywiście jesteś idiotą?! Pytasz się mnie o to samo już trzeci raz!","I pomyśleć tylko, jak taki idiota mógł zostać kapitanem...","blok",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Dziękuję, przyjacielu, bardzo mi pomogłeś!","Tak, tak, oczywiście.","Ojej, ojej, nie denerwuj się tak. Po prostu zapomniałem.","Ty mi to mówisz?...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Nie, kumplu, nigdy nie słyszałem o kimś takim. Zapytaj dookoła - może ktoś go zna...","Już pytałeś mnie o tego człowieka, i powiedziałem ci, że nie wiem!","Żartujesz sobie ze mnie, czy naprawdę jesteś idiotą?! Pytasz o to samo już trzeci raz!","I pomyśleć, że taki idiota mógł zostać kapitanem...","blok",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Rozumiem. Cóż, dzięki mimo wszystko.","Tak, tak, dobrze.","Oj, oj, nie denerwuj się tak. Po prostu zapomniałem.","Ty mi to mówisz?...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Niestety, teraz nie mogę ci pomóc - nikt z ludzi, których znam, nie chciałby służyć pod twoim dowództwem. Ale mogę ci dać radę - porozmawiaj z tym marynarzem, który właśnie zajął stół tuż za tobą. On i jego kumple właśnie opuścili jeden statek handlowy. Może zgodzą się pójść z tobą.";
			link.l1 = "W porządku, właśnie tak zrobię! Bardzo ci dziękuję!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Nie mogę ci powiedzieć nic konkretnego, przyjacielu. W tej chwili żadni nawigatorzy nie odwiedzają mojego miejsca. Spróbuj zapytać w porcie - być może, ludzie będą wiedzieli więcej.";
			link.l1 = "Rozumiem. Dobrze, pójdę porozmawiać z ludźmi.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Natychmiast, Panie!.. Najlepsze francuskie wino!"+sld.name+"! Przygotuj najlepszy pokój dla gości! To będzie 1000 peso, panie.";
			link.l1 = "Prosze.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Wypad, szelmo! Nie będziesz mi zajmował cennych miejsc dla płacących klientów!";
				link.l1 = "Dobrze, dobrze...";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Tak - i przestraszyć wszystkich moich klientów tym, że strażnicy wyciągają ludzi z mojej karczmy? A niektórzy z moich klientów nie lubią przebywać w pobliżu żołnierzy. To ich denerwuje, rozumiesz? Nie chcę zrujnować swojej reputacji...";
				link.l1 = "Hmm, a co jeśli rozwiążę twój problem?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Czy to aby na pewno dobry pomysł? Jest jakimś zawodowym najemnikiem, w dodatku uzbrojonym...";
				link.l1 = "Hmm, masz rację, nie chcę się kłócić z uzbrojonym najemnikiem...";
				link.l1.go = "Exit";
				link.l2 = "Cóż, mi też daleko do "+GetSexPhrase("zakonnika","zakonnicy")+"... I nadal chcę wynająć pokój.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "No cóż, jeśli możesz, ekhem... przekonać go do wyniesienia się, to pokój jest twój aż do rana. Oczywiście za darmo.";
				link.l1 = "Wiesz, zmieniłem zdanie. Nie mam ochoty przekonywać nikogo.";
				link.l1.go = "Exit";
				link.l2 = "Patrz uważnie. Twój nieproszony gość zaraz wyleci z twojej karczmy niczym wielka mewa.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Rozumiem. To będzie pięć peso.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Oczywiście, proszę bardzo.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "Właściwie, wiesz co... Może innym razem. Spędzę resztę dnia na nogach.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Mądra decyzja. To będzie pięć peso, i dobranoc dla ciebie.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Proszę bardzo, a dziękuję - dobranoc.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "Po dłuższym zastanowieniu, nie chce mi się spać. Poszwendam się po mieście, wdychając nocne powietrze.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Oczywiście, Helen. To będzie dziesięć peso.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Oczywiście, proszę bardzo.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "Właściwie... Mogłabym zrobić coś pożytecznego przez cały dzień. Może innym razem.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Jak sobie życzysz, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "Możesz nawet poczuć się senna po dobrym spacerze.";
			link.l1 = "Ha-ha, może.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Jak uważasz za stosowne.";
			link.l1 = "Cóż, do następnego razu.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Oczywiście, Helen, zamieniam się w słuch.";
			link.l1 = "Jakie są najnowsze wiadomości czy też ciekawe plotki w mieście?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "Płaci trzy razy więcej niż normalnie, więc... sam pan rozumie. I nie radzę mu odmawiać - ma trudny charakter. Zwłaszcza ostatnio.";
			link.l1 = "Co się z nim dzieje?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Obsesja, o to chodzi. Na początku był hojny, dobry facet. Jego marynarze szastali pieniędzmi w tawernach, kupowali prezenty dziewczynom. Prawdziwe święto się zaczynało, gdy 'Lady Beth' zawijała do portu. A teraz? Teraz tylko kupują prowiant i zaciągają ludzi bez zastanowienia. Jakby nie potrzebowali marynarzy, tylko rąk do pracy. Ale może pan sam z nim porozmawiać.";
			link.l1 = "Może zajrzę. Dzięki.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
