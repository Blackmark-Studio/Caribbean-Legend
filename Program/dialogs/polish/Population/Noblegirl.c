//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. Płyniesz pod banderą "+NationNameGenitive(sti(pchar.nation))+", kapitanie. Nie mam ochoty rozmawiać z wrogiem mojego kraju. Hmph!";
					link.l1 = "Ah, tak. Prawdziwy patriota...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Czego chcesz ode mnie, "+GetAddress_Form(NPChar)+"? Nie przystoi zwykłemu żeglarzowi rozmawiać ze szlachetną damą, ale słucham cię.","Och, a czego taki odważny kapitan ode mnie chce?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"Nie zajmę ci dużo czasu, chcę tylko zapytać...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Muszę wiedzieć, co się dzieje w waszej kolonii.","Potrzebuję pewnych informacji.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Całe miasto jest na krawędzi - przybył don Fernando de Alamida, królewski inspektor. Wiesz, widziałem tu wiele, ale to... To nie żal zmienia ludzi, ale to, jak sobie z nim radzą. Mówią, że stał się innym człowiekiem po śmierci ojca. Teraz nie znajdziesz bardziej nieprzekupnego i... bezwzględnego sługi Korony w całym Archipelagu.","Spójrz tylko na 'Świętą Miłosierdzie'! Mówią, że sam król nakazał jej budowę według specjalnych projektów. I zauważ - ani jednej rysy. Jakby sama Matka Boska ją chroniła. Choć słyszałem plotki... może to wcale nie Matka Boska.","Wiesz, ile razy próbowali zabić don Fernando? Dwanaście ataków na otwartych wodach - i to tylko w zeszłym roku! Cóż, z tak lojalną i wyszkoloną załogą oraz pod opieką Pana - przetrwa i trzynasty!"),LinkRandPhrase("Słyszałeś? Don Fernando de Alamida przybył do naszego miasta i mówią, że jest gdzieś na ulicach w tej chwili. Chciałbym go zobaczyć na własne oczy...","Skomplikowany człowiek, ten don Fernando. Niektórzy mówią, że jest zbawcą, oczyszczającym Ojczyznę z plugastwa. Inni szepczą, że coś w nim pękło po śmierci ojca i wkrótce wszyscy będziemy płakać. Ale powiem ci jedno: nie bój się jego. Bój się tych, którzy uczynili go takim, jakim jest.","Przystojny mężczyzna, ten don Fernando! Ale wiesz, co jest dziwne? Jakby nikogo nie zauważał. Tylko obowiązek i służba. Słyszałam, że była jakaś dziewczyna... ale po spotkaniu z jakimś księdzem, całkowicie odrzucił ziemskie przyjemności. Jakby złożył ślub."),RandPhraseSimple(RandPhraseSimple("Cholerny inspektor! Gdy jest tutaj - miasto jest jak martwe. Brak handlu, brak zabawy. Nawet oddychanie, wydaje się, musi być cichsze. I wiesz, co jest najbardziej przerażające? To samo dzieje się w każdym porcie. Jak w zegarku. Jego Królewska Mość nie mógłby celowo wymyślić tej tortury dla nas wszystkich!","Don Fernando ponownie odwiedził sierociniec. Hojnie daruje, modli się godzinami. Takiego godnego męża należy stawiać za przykład przeklętym defraudantom!"),RandPhraseSimple("Ha! 'Święty' Fernando znowu zamknął wszystkie burdele. Cóż, nieważne, wkrótce wypłynie i znów je otworzą.","Inspe... inspektor przybył, oto co! Don Fernando de Almeyda, czy jak mu tam, Alamida! Tak ważny, że sam gubernator chodzi wokół niego na paluszkach. Mówią, że patrzy ci w oczy i od razu widzi wszystkie twoje grzechy. Przerażające!")));
					link.l1 = "... ";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Czy powinienem się powtórzyć? Nie chcę być podejrzewany o przyjaźń z "+NationNameAblative(sti(pchar.nation))+"Precz, albo zawołam straż! Chętnie z tobą porozmawiają.";
					link.l1 = "Dobrze, dobrze, uspokój się. Już odchodzę.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Co? Znowu ty? Poszukaj sobie kogoś innego do rozmowy. Kręci się tu mnóstwo pospólstwa, oni bardziej pasują do ciebie. Muszę już iść, dziś wieczorem będzie bankiet w rezydencji gubernatora, a moja fryzura jeszcze nie jest gotowa!","Nie, teraz naprawdę zaczynasz mnie denerwować! Nie rozumiesz tego? Czy jesteś przygłupi?","Panie, zaczynam podejrzewać, że nie tylko jesteś idiotą, ale i łajdakiem oraz gburem. Ostrzegam cię, że zawołam mojego męża, jeśli nie przestaniesz mnie nękać swoimi głupimi pytaniami!","Jeszcze jedno słowo i powiem komendantowi, żeby coś z tobą zrobił!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Rozumiem. Żegnaj.","Tak-tak, pamiętam, tylko zapomniałem zapytać...","Źle mnie zrozumiałeś...","Spokojnie, pani, już odchodzę...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Dobrze, posłuchajmy.","Och, dobrze. Czego chcesz?","Pytania? Dobrze, marynarzu, słucham.");
			link.l1 = LinkRandPhrase("Czy możesz mi opowiedzieć ostatnie plotki z tego miasta?","Czy wydarzyło się tu ostatnio coś interesującego?","Jakieś wieści z Karaibów, moja pani?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Jesteś szalony?! Przerażasz mnie! Schowaj broń, albo powiem komendantowi, żeby cię powiesił w fortecy!","Oszalałeś?! Przerażasz mnie! Schowaj broń, albo powiem komendantowi, żeby cię powiesił w fortecy!");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz.","Dobrze.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
