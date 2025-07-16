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
			dialog.text = LinkRandPhrase("¡Oh mi Señor, estoy tan contento de haberte encontrado!","¡Finalmente alguien!","¡Oh Dios mío, estoy tan feliz de verte!");
			Link.l1 = LinkRandPhrase("¿Qué pasa, cariño?","¿Algún problema, cariño?","No te alteres tanto, no es bueno para la salud de una jovencita. Ahora, solo dime, ¿qué sucedió?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("Mi amiga... es tan valiente... ¡se metió en un pozo abandonado!","¡Mi amiga bajó a un pozo abandonado, y aún no ha salido! ¡Ha pasado varias horas allí!","¡Mi amigo acaba de desaparecer en un pozo abandonado!");
			Link.l1 = "¿Y por qué diablos entró ahí?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "¡Oh, ella teme absolutamente a todo! Escuchó que había una mazmorra llena de oro, así que bajó allí... ¡Pero yo no soy un tonto, ni siquiera lo pensaría!";
			Link.l1 = "Es cierto, no hay nada para ti que hacer en tal lugar.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "¿Pero qué se supone que debo hacer ahora? Por favor, ayúdala, por el amor de Dios!";
			Link.l1 = "Está bien, lo averiguaré. Y mejor te vas a casa, no hay nada que hacer aquí para ti.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Estos son tus problemas, no quiero perder mi tiempo. Adiós...";
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
            dialog.text = "No quiero hablar con alguien tan insensible "+GetSexPhrase("coágulo","zorra")+". ¡Pierde vista!";
			Link.l1 = "Je, qué perra...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "¡Oh Dios mío, estoy tan contento de verte!";
			Link.l1 = "¿Qué pasa, belleza?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "¡Me he perdido aquí! ¡Oh Dios mío, estoy tan terriblemente asustado!!!";
			Link.l1 = "Bueno, estás bien ahora. Sígueme, te mostraré el camino. Una vez que estás en la superficie, corre a casa y reza para que nunca te vuelva a ver aquí!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Como usted dice, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Bien.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Vaya, parece que alguien más se interesó en esta mazmorra!";
			Link.l1 = "Belleza, ¿qué haces aquí?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "¡No es asunto tuyo!";
			Link.l1 = "Vaya, esa es una respuesta de un millón de pesos...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "Por dos millones. ¿Simplemente seguirás tu propio camino? No me importas en lo más mínimo.";
			Link.l1 = "Bueno, el sentimiento es mutuo, pero tu amigo de arriba estaba terriblemente preocupado por ti...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "¡Qué tonta! Se cagaría en los pantalones de miedo, y piensa que soy igual que ella.";
			Link.l1 = "Vaya, seguro que no te gusta ella. El diablo en falda, eso es lo que eres.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Eh, ¡elige tus palabras! Y mejor aún, simplemente pérdete.";
			Link.l1 = "Bueno, si no necesitas mi ayuda...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "¡No, no lo hago!";
			Link.l1 = "Entonces adiós y buena suerte para ti.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "¿Tú otra vez? Piérdete, no quiero verte más...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
