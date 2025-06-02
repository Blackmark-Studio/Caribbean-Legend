void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Podniesiono alarm w mieście. Wszyscy cię szukają! Na twoim miejscu nie czekałbym tu zbyt długo.","Cała straż miejska przeszukuje miasto, próbując cię znaleźć. Nie jestem idiotą i nie zamierzam z tobą rozmawiać!","Uciekaj, kamracie, zanim żołnierze zrobią z ciebie siekaninę..."),LinkRandPhrase("Czego potrzebujesz, łotrze?! Straż miejska depcze ci po piętach. Daleko nie uciekniesz, brudny piracie!","Precz z mojego domu, morderco! Straże!!","Nie boję się ciebie, łotrze! Wkrótce cię powieszą, nie uciekniesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, nie martwię się zbytnio o alarm...","Nie mają szans mnie złapać."),RandPhraseSimple("Zamknij swój pysk, "+GetWorkTypeOfMan(npchar," ")+", albo odetnę ci ten przeklęty język!","Heh, "+GetWorkTypeOfMan(npchar," ")+", ty też chcesz polować na pirata! Słuchaj, przyjacielu, zachowaj spokój, a przeżyjesz..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"Nie widziałem cię wcześniej, señor. Czy mogę przypuszczać, że jesteś kapitanem... Czy zgadłem? Nazywam się "+GetFullName(npchar)+", a mój sklep jest do Twoich usług. Złoto, srebro i wiele więcej, by wzbudzić zainteresowanie ciekawskiego człowieka.";
				Link.l1 = "Rozumiem. Jestem "+GetFullName(pchar)+"Miło cię poznać, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+"¡Señor! Cieszę się, że znów cię widzę w moim sklepie. Czy chciałbyś nabyć trochę złotych samorodków? A może interesują cię dziś minerały?";
				link.l1 = "Pokaż mi swoje towary, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "Nie, nie potrzebuję niczego, "+npchar.name+"   Zatrzymałem się tylko, by się z tobą przywitać.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Jak i ja, señor. Czy chciałbyś obejrzeć moje towary? Jestem pewien, że mam coś, co cię zainteresuje.";
			link.l1 = "Jestem tu po raz pierwszy i chciałbym dowiedzieć się trochę więcej o tej osadzie.";
			link.l1.go = "info";
			link.l2 = "Pokaż mi zatem, co masz na sprzedaż.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Nasze małe miasteczko zostało zbudowane dzięki kopalni złota. Wydobywają tu rudę złota, srebro i złote samorodki. Czasami nawet klejnoty. Kiedyś mieliśmy tu tylko garnizon, dopóki nie dołączyli do nas przyjaźni Indianie i kilku białych osadników\nIgnacio Ortega zbudował tawernę i uczynił nasze życie nieco weselszym. Różnej maści awanturnicy odwiedzają to miejsce z głupim zamiarem obrabowania nas. Nie mamy tu sądu, więc ich liczba zmniejszyła się, gdy powiesiliśmy kilku idiotów na środku miasta\nRuda złota jest wysyłana na statki pod ochroną żołnierzy i przyjaznych Indian, jednak samorodki możesz kupić właśnie tutaj, w tym sklepie\nPoza tym czasem mam do zaoferowania bardzo interesujące minerały, więc odwiedzaj mnie, gdy masz czas, zawsze uzupełniam swoje zapasy.";
			link.l1 = "Dziękuję za ciekawą opowieść! Zapamiętam ją.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rozbój w biały dzień!!! Co się tu dzieje?! Poczekaj, chwileczkę, kolego...","Hej, co tam robisz?! Próbujesz mnie okraść? Teraz masz przechlapane...","Zaczekaj, co u diabła robisz? Okazuje się, że jesteś złodziejem! Uznaj to za koniec drogi, draniu...");
			link.l1 = LinkRandPhrase("Diabeł!!","Caramba!!","O cholera!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
