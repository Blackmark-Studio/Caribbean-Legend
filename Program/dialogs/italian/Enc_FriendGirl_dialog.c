void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("Oh mio Signore, sono così felice di averti incontrato!","Finalmente qualcuno!","Oh mio Dio, sono così felice di vederti!");
			Link.l1 = LinkRandPhrase("Cosa c'è, bella?","Hai problemi, cara?","Non ti agitare così tanto - non fa bene alla salute di una giovane signora. Ora, dimmi solo - cosa è successo?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("La mia amica... è così coraggiosa... è entrata in un pozzo abbandonato!","La mia amica è scesa in un pozzo abbandonato, e non è ancora uscita! È rimasta là dentro per diverse ore!","Il mio amico è appena scomparso in un pozzo abbandonato!");
			Link.l1 = "E perché diavolo è entrata lì?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Oh, sai, ha paura di assolutamente tutto! Ha sentito dire che c'era una prigione piena d'oro, così ci è andata... Ma io non sono uno sciocco, non ci penserei nemmeno!";
			Link.l1 = "È vero, non c'è nulla per te da fare in un posto del genere.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "Ma cosa dovrei fare ora? Per favore, aiutala, per l'amor del cielo!";
			Link.l1 = "Bene, lo capirò. E sarebbe meglio che tu tornassi a casa, non c'è nulla per te da fare qui.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Questi sono i tuoi problemi, non voglio perdere il mio tempo. Addio...";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirlF.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirlF.locationId; //флаг для открытия релоада
				string model[10];
				model[0] = "citiz_41";
				model[1] = "citiz_42";
				model[2] = "citiz_43";
				model[3] = "citiz_44";
				model[4] = "citiz_45";
				model[5] = "citiz_46";
				model[6] = "citiz_47";
				model[7] = "citiz_48";
				model[8] = "citiz_49";
				model[9] = "citiz_50";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						sld.money = iRank*200+1000+rand(500);
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);// лесник изменил группу чтобы ядом таино травить можно было
						LAi_group_Attack(sld, Pchar);// лесник добавил атаку на пчара а то у некоторых баг что они не нападают.
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //и правда девка 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, PIRATE, 1, false, "citizen"));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground"+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая// лесник - раскоментил itemp
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
			   // LAi_SetStayType(sld);
				LAi_SetCitizenType(sld);// чтоб ходила по пещере. лесник
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				GetCharacterPos(pchar, &locx, &locy, &locz); // и ниже - ищем ближейший локатор лесник.
	            ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DialogExit();
		break;			
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "Non voglio parlare con un tale insensibile "+GetSexPhrase("grumo","sgualdrina")+". Sparisci!";
			Link.l1 = "Eh, che stronza...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Oh mio Dio, sono così felice di vederti!";
			Link.l1 = "Come va, bellezza?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "Mi sono perso qui! Oh mio Dio, ho così terribilmente paura!!!";
			Link.l1 = "Bene, adesso stai bene. Seguimi, ti mostrerò la strada. Una volta in superficie, corri a casa e prega di non vederti mai più qui!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Come dici, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Bene.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Caspita, sembra che qualcun altro si sia interessato a questa grotta!";
			Link.l1 = "Bella, cosa stai facendo qui?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "Non sono affari tuoi!";
			Link.l1 = "Caspita, questa è una risposta da un milione di pesos...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "Per due milioni. Andrai per la tua strada? Non mi importa niente di te.";
			Link.l1 = "Ebbene, il sentimento è reciproco, ma il tuo amico lassù era malato di preoccupazione per te...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "Che sciocca! Si caccherebbe addosso dalla paura, e pensa che io sia come lei.";
			Link.l1 = "Caspita, sicuramente non ti piace. Il diavolo in gonna - ecco chi sei tu.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Ehi, scegli le tue parole! E meglio ancora, semplicemente sparisci.";
			Link.l1 = "Bene, se non hai bisogno del mio aiuto...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "No, non lo faccio!";
			Link.l1 = "Allora addio e buona fortuna a te.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "Di nuovo tu? Vattene, non voglio più vederti...";
			Link.l1 = "Uhmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
