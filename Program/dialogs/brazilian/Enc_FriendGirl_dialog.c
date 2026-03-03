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
			dialog.text = LinkRandPhrase("Meu Deus, estou tão feliz por ter te conhecido!","Finalmente, alguém!","Meu Deus, que bom te ver!");
			Link.l1 = LinkRandPhrase("O que está acontecendo, querido?","Algum problema, querido?","Não fique tão agitada – isso não faz bem para a saúde de uma jovem. Agora, me diga – o que aconteceu?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("Minha amiga... ela é tão corajosa... ela desceu em um poço abandonado!","Minha amiga desceu em um poço abandonado e até agora não saiu! Já faz várias horas que ela está lá!","Meu amigo acabou de desaparecer em um poço abandonado!");
			Link.l1 = "E por que diabos ela entrou lá?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Ah, você sabe, ela tem medo de absolutamente tudo! Ouviu dizer que havia uma masmorra cheia de ouro, então desceu lá... Mas eu não sou bobo, nem pensaria nisso!";
			Link.l1 = "É isso mesmo, não há nada para você fazer em um lugar como este.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "Mas o que eu faço agora? Por favor, ajude ela, pelo amor de Deus!";
			Link.l1 = "Tá bom, eu vou dar um jeito. E é melhor você ir pra casa, não tem nada pra você fazer aqui.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Esses são seus problemas, não quero perder meu tempo. Adeus...";
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
            dialog.text = "Eu não quero conversar com uma pessoa tão insensível "+GetSexPhrase("coágulo","vadia")+". Cai fora!";
			Link.l1 = "Heh, que vadia...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Meu Deus, que bom te ver!";
			Link.l1 = "E aí, linda?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "Me perdi aqui! Meu Deus, estou morrendo de medo!!!";
			Link.l1 = "Bem, agora você está bem. Me siga, eu vou te mostrar o caminho. Quando chegar à superfície, corra para casa e reze para que eu nunca mais te veja aqui!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Como quiser, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Tudo bem.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Puxa vida, parece que alguém mais se interessou por esta masmorra!";
			Link.l1 = "Beleza, o que você está fazendo aqui?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "Isso não te diz respeito!";
			Link.l1 = "Caramba, essa resposta vale um milhão de pesos...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "Por dois milhões. Vai seguir seu caminho? Não tô nem aí pra você.";
			Link.l1 = "Bem, o sentimento é recíproco, mas seu amigo lá em cima estava morrendo de preocupação com você...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "Que idiota! Ela se cagaria de medo, e ainda acha que eu sou igual a ela.";
			Link.l1 = "Você com certeza não gosta dela. O diabo de saia – é isso que você é.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Ei, cuidado com o que fala! E melhor ainda, desapareça daqui.";
			Link.l1 = "Bem, se você não precisa da minha ajuda...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "Não, eu não quero!";
			Link.l1 = "Então adeus, e boa sorte pra você.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "Você de novo? Cai fora, não quero mais te ver...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
