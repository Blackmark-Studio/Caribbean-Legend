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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Du wagst es hierher zu kommen?! Kühne Aktion...","Wie konnten diese Dummköpfe einen Feind eindringen lassen?! Das ist mir unbegreiflich...","Nun, meine Wachen sind nutzlos, wenn irgendein Idiot in meiner Residenz herumläuft..."),LinkRandPhrase("Was willst du, Bastard?! Meine Soldaten haben dich bereits aufgespürt und du wirst nicht entkommen"+GetSexPhrase(", dreckiger Pirat"," dreckiger Pirat")+"!","Dreckiger Mörder, verschwinde von meiner Residenz! Wachen!!!","Ich habe keine Angst vor dir, Bastard! Du wirst gehängt werden, du wirst nicht davonkommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Soldaten kosten nichts...","Sie werden mich niemals erwischen."),RandPhraseSimple("Halt den Mund, "+GetWorkTypeOfMan(npchar,"")+", oder ich schneide deine Zunge ab und stopfe sie in deinen Hals...","Ich würde dir sagen, Kumpel: sitz ruhig da, und du könntest noch einen anderen Tag erleben ..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Feind in meiner Residenz! Alarm!!!";
				link.l1 = "Scheiße!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" Herr. Ich bin "+GetFullName(npchar)+", Kommandant der Mine von Lost-Tekes, die gehört "+NationKingsName(npchar)+". Nun, würden Sie so freundlich sein, mir den Zweck Ihres Besuchs zu nennen, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Es ist mein erstes Mal hier und ich möchte mehr über diese Siedlung und ihre Gesetze erfahren...";
				link.l1.go = "info";
				link.l2 = "Nur um Sie zu begrüßen, ich gehe schon.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Wieder Sie, Herr? Was wollen Sie sonst noch?";
			link.l1 = "Es ist nichts. Ich gehe.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Ich respektiere solche Disziplin. Nun, ich werde Sie auf den neuesten Stand bringen, da Sie so interessiert sind.\nDie Los-Teques-Mine ist Eigentum der spanischen Krone. Wir fördern hier silbernes und goldenes Roherz sowie Silber- und Goldnuggets. Alles Gold und Silber gehört Spanien und wird in die Alte Welt transportiert.\nDie Mine ist gut bewacht, eine Einheit von Elite-Soldaten der Spanier ist immer hier stationiert. Piraten haben mehrere Versuche unternommen, unsere Mine zu überfallen, aber die Folgen waren immer schlecht... für sie.\nWie Sie sehen können, ist es eine kleine Stadt. Wir haben eine Taverne und einen Laden. Dort können Sie Gold- und Silberbarren zu einem guten Preis kaufen. Außerdem kann unser Quartiermeister, der auch ein Händler im Laden ist, Ihnen andere interessante Metalle und Erze verkaufen.\nDie meisten unserer Arbeiter sind Sträflinge, aber wir haben auch eine kleine Anzahl von schwarzen Sklaven. Wie Sie sehen können, haben wir immer Bedarf an neuer Arbeitskraft, jeden Tag stirbt mindestens einer dieser verfluchten Sträflinge.\nWenn Sie uns also Sklaven bringen, tauschen wir Nuggets gegen sie ein. Wenden Sie sich für solche Angelegenheiten an unseren leitenden Ingenieur. Sie finden ihn im Stollen.\nBenehmen Sie sich hier. Beginnen Sie keine Duelle oder Kämpfe, versuchen Sie nicht, etwas zu stehlen, vor allem Gold oder Silber. Wir haben hier kein Gefängnis, aber wir haben ein Kriegsgericht.\nDas ist im Grunde genommen alles. Befolgen Sie diese einfachen Regeln und Sie werden keine Probleme haben. Sie dürfen sich frei in der Mine bewegen. Vergessen Sie nicht, die Taverne zu besuchen, sie bieten bestimmte... Dienstleistungen mit meiner Erlaubnis an. Willkommen!";
			link.l1 = "Mein Dank!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Raub!!! Das ist inakzeptabel! Mach dich bereit, "+GetSexPhrase("Kumpel","Mädchen")+"...";
			link.l1 = LinkRandPhrase("Scheiße!","Verdammt noch mal!!","Verdammt!");
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
