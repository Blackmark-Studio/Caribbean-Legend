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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Você ousa aparecer aqui?! Que ousadia...","Como aqueles idiotas puderam deixar o inimigo invadir?! Isso me escapa...","Bem, meus guardas não servem para nada se algum idiota está perambulando pela minha residência..."),LinkRandPhrase("O que você quer, bastardo?! Meus soldados já te encontraram e você não vai escapar."+GetSexPhrase(", pirata imundo"," pirata imundo")+"!","Assassino imundo, saia da minha residência! Guardas!!!","Eu não tenho medo de você, seu bastardo! Você vai ser enforcado, não vai escapar..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Soldados não custam nada...","Eles nunca vão me pegar."),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu corto sua língua e enfio goela abaixo...","Eu te digo, camarada: fique quieto, e talvez ainda veja outro dia..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Inimigo na minha residência! Alarme!!!";
				link.l1 = "Merda!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" Senhor. Eu estou "+GetFullName(npchar)+", comandante da mina Lost-Tekes, que pertence a "+NationKingsName(npchar)+". Agora, poderia me dizer o motivo da sua visita, "+GetAddress_Form(NPChar)+".";
				link.l1 = "É a minha primeira vez aqui e quero saber mais sobre este povoado e suas leis...";
				link.l1.go = "info";
				link.l2 = "Só queria cumprimentá-lo, já estou de saída.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Você de novo, senhor? O que mais deseja?";
			link.l1 = "Não é nada. Estou indo embora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "I respect such discipline. Well, I'll bring you up to speed in that case, since you are that interested.\nLos-Teques mine is the property of the Spanish Crown. We mine silver and gold ore here, as well as silver and gold nuggets. All gold and silver belong to Spain and are transported to the Old World.\nThe mine is well guarded; a unit of elite Spanish soldiers is always stationed here. Pirates have made several attempts to rob our mine, but the consequences were always bad... for them.\nAs you can see, it is a small town. We have a tavern and a store. You can buy gold and silver ingots for a good price there. Besides, our quartermaster, who is also the merchant in the store, can sell you other interesting metals and ores.\nMost of our workers are convicts, but we also have a small number of black slaves. As you can see, we are always in need of new manpower; every day at least one of these blasted convicts dies.\nSo, if you bring us slaves, we will exchange nuggets for them. Contact our lead engineer for such matters. You can find him in the shaft.\nBehave yourself here. Don't start duels or fights, don't try to steal anything, especially gold or silver. We don't have a prison here, but we do have a court martial.\nThat's pretty much it. Follow these simple rules and you will have no problems. You are allowed to move freely within the mine. Don't forget to visit the tavern; they perform certain... services with my permission. Welcome!";
			link.l1 = "Meus agradecimentos!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Roubo!!! Isso é inaceitável! Prepare-se, "+GetSexPhrase("amigo","garota")+"...";
			link.l1 = LinkRandPhrase("Merda!","Caramba!!","Droga!");
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
