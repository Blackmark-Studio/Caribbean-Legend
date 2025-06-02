void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Śmiesz tu przychodzić?! Śmiałe działanie...","Jak ci głupcy mogli dopuścić do inwazji wroga?! Nie pojmuję tego...","Cóż, moi strażnicy są bezużyteczni, jeśli jakiś idiota kręci się po mojej rezydencji..."),LinkRandPhrase("Czego chcesz, bękarcie?! Moi żołnierze już cię namierzyli i nie uciekniesz."+GetSexPhrase(", plugawy piracie","plugawy pirat")+"!","Brudny morderco, precz z mojej rezydencji! Strażnicy!!!","Nie boję się ciebie, bękarcie! Zawiśniesz, nie uciekniesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Żołnierze nic nie kosztują...","Nie złapią mnie nigdy."),RandPhraseSimple("Zamknij gębę, "+GetWorkTypeOfMan(npchar," ")+", albo odetnę ci język i wepchnę go w gardło...","Rzekłbym ci, kumie: siedź cicho, a może jeszcze ujrzysz kolejny dzień..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Wróg w mojej rezydencji! Alarm!!!";
				link.l1 = "Cholera!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" Sir. Jestem "+GetFullName(npchar)+", komendant kopalni Lost-Tekes, która należy do "+NationKingsName(npchar)+"Teraz, czy byłbyś tak uprzejmy, aby powiedzieć mi cel swojej wizyty, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Jestem tu po raz pierwszy i chcę dowiedzieć się więcej o tej osadzie i jej prawach...";
				link.l1.go = "info";
				link.l2 = "Chciałem tylko cię pozdrowić, już wychodzę.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Znowu ty, sir? Czego jeszcze chcesz?";
			link.l1 = "To nic. Wychodzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Szanuję taką dyscyplinę. Cóż, w takim razie przybliżę ci sytuację, skoro jesteś tak zainteresowany.\nKopalnia Los-Teques jest własnością hiszpańskiej korony. Wydobywamy tutaj srebrną i złotą rudę, a także srebrne i złote samorodki. Wszystko złoto i srebro należy do Hiszpanii i jest transportowane do Starego Świata.\nKopalnia jest dobrze strzeżona, zawsze stacjonuje tu oddział elitarnych hiszpańskich żołnierzy. Piraci kilkakrotnie próbowali obrabować naszą kopalnię, ale konsekwencje zawsze były złe... dla nich.\nJak widzisz, to małe miasteczko. Mamy karczmę i sklep. Możesz tam kupić złote i srebrne sztabki za dobrą cenę. Poza tym, nasz kwatermistrz, który jest także kupcem w sklepie, może ci sprzedać inne interesujące metale i rudy.\nWiększość naszych pracowników to skazańcy, ale mamy też niewielką liczbę czarnych niewolników. Jak widzisz, zawsze potrzebujemy nowych rąk do pracy, każdego dnia przynajmniej jeden z tych przeklętych skazańców umiera.\nWięc, jeśli przyprowadzisz nam niewolników, wymienimy je na samorodki. Skontaktuj się z naszym głównym inżynierem w tej sprawie. Znajdziesz go w szybie.\nZachowuj się tutaj przyzwoicie. Nie zaczynaj pojedynków czy bójek, nie próbuj niczego ukraść, zwłaszcza złota czy srebra. Nie mamy tutaj więzienia, ale mamy sąd wojenny.\nTo by było na tyle. Przestrzegaj tych prostych zasad, a nie będziesz miał problemów. Masz prawo poruszać się swobodnie po kopalni. Nie zapomnij odwiedzić karczmy, za moim pozwoleniem świadczą tam pewne... usługi. Witaj!";
			link.l1 = "Moje podziękowania!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Rabunek!!! To jest nie do przyjęcia! Przygotuj się, "+GetSexPhrase("kamrat","dziewczyna")+"...";
			link.l1 = LinkRandPhrase("Cholera!","Carramba!!","Do diabła!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
