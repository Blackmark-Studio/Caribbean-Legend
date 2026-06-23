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
			dialog.text = LinkRandPhrase("Oh mon Seigneur, je suis si heureux de vous avoir rencontre!","Enfin quelqu'un !","Oh mon Dieu, je suis si heureux de te voir!");
			Link.l1 = LinkRandPhrase("Quoi de neuf, chérie?","Des problèmes, chérie?","Ne vous agitez pas autant - ce n'est pas bon pour la santé d'une jeune dame. Maintenant, dites-moi simplement - qu'est-ce qui s'est passé?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("Mon ami... elle est si courageuse... elle est entrée dans un puits abandonné!","Mon amie est descendue dans un puits abandonné, et elle n'est toujours pas sortie ! Elle y a passé plusieurs heures !","Mon ami a simplement disparu dans un puits abandonné!");
			Link.l1 = "Et pourquoi diable est-elle entrée là-dedans?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Oh, tu sais, elle a peur de absolument tout! Elle a entendu dire qu'il y avait un donjon plein d'or, alors elle y est descendue... Mais je ne suis pas un imbécile, je n'y penserais même pas!";
			Link.l1 = "C'est vrai, il n'y a rien pour toi à faire dans un tel endroit.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "Mais que suis-je censé faire maintenant ? S'il vous plaît, aidez-la, pour l'amour du ciel !";
			Link.l1 = "D'accord, je vais le comprendre. Et tu ferais mieux de rentrer chez toi, il n'y a rien pour toi à faire ici.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Ce sont vos problèmes, je ne veux pas perdre mon temps. Adieu...";
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
						iRank = int(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						LAi_CharacterDisableDialog(sld);
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
            dialog.text = "Je ne veux pas parler avec un tel insensible "+GetSexPhrase("caillot","garce")+". Dégage !";
			Link.l1 = "Heh, quelle garce...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Oh mon Dieu, je suis tellement heureux de te voir!";
			Link.l1 = "Quoi de neuf, beauté?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "Je me suis perdu ici ! Mon Dieu, j'ai tellement peur !!!";
			Link.l1 = "Eh bien, tu vas bien maintenant. Suis-moi, je te montrerai le chemin. Une fois que tu es à la surface, cours chez toi, et prie pour que je ne te revoie jamais ici!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Comme vous dites, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "D'accord.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Wow, il semble que quelqu'un d'autre s'est intéressé à ce donjon !";
			Link.l1 = "Belle, que fais-tu ici?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "Ce ne sont pas vos affaires!";
			Link.l1 = "Wow, c'est une réponse pour un million de pesos...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "Pour deux millions. Tu vas simplement suivre ton propre chemin? Je me fiche de toi.";
			Link.l1 = "Eh bien, le sentiment est réciproque, mais votre ami là-haut se faisait un sang d'encre pour vous...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "Quelle idiote! Elle ferait dans son pantalon de peur, et elle pense que je suis pareil à elle.";
			Link.l1 = "Wow, tu ne l'aimes sûrement pas. Le diable en jupe - c'est qui tu es.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Hey, choisissez vos mots! Et mieux encore, disparaissez simplement.";
			Link.l1 = "Eh bien, si vous n'avez pas besoin de mon aide...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "Non, je ne le fais pas!";
			Link.l1 = "Alors adieu et bonne chance à toi.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "Vous encore? Dégagez, je ne veux plus vous voir...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
