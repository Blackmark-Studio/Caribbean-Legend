// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chuanzhang. Meu nome é Longway. Longway coloca seu navio sob seu comando. Longway também está sob seu comando. Por ordem do senhor Rodenburg.";
			link.l1 = "Saudações, Longway. Charles de Maure, ao seu dispor. Você tem alguma pista sobre a operação para eliminar Jacob van Berg?";
			link.l1.go = "Longway_friend";
			link.l2 = "Bom te ver, Longway. Meu nome é Charles de Maure. Sem tempo a perder – o senhor Rodenburg valoriza trabalho rápido e de qualidade. Onde está Jacob van Berg escondido agora?";
			link.l2.go = "Longway_neutral";
			link.l3 = "Bem, e o meu é Charles de Maure! Vamos torcer para que os nossos trabalhem bem juntos! Então, senhor Longway, por favor, me diga, onde devemos procurar Jacob van Berg?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Longway tem certeza de que vamos trabalhar bem juntos, chuanzhang. Jacob van Berg está atualmente em "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Marquei um encontro com ele na taverna local. Ele estará lá.";
			link.l1 = "Vamos zarpar!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "Ordem da lei do senhor Rodenburg para Longway... Jacob van Berg atualmente em "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Marquei um encontro com ele na taverna local. Ele estará lá.";
			link.l1 = "Vamos zarpar!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			Notification_Approve(false, "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "Longway fará tudo o que puder, chuanzhang. E Jacob van Berg está atualmente em "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". Marquei um encontro com ele na taverna local. Ele estará lá.";
			link.l1 = "Vamos zarpar!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			Notification_Approve(true, "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			ForceHeroAutolevel(npchar);
			SetCharacterPerk(npchar, "Captain");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "O que Longway pode fazer, chuanzhang?";
			link.l1 = "Nada por enquanto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Seu idiota, seu tolo mongol, chuanzhang! Tínhamos uma tarefa simples – capturar o 'Mirage' sem perder o 'Meifeng'. Ela era um alvo fácil sem o chuanzhang, mas mesmo assim você falhou\nLongway não vai mais te servir, nem quer te ver. Longway tem certeza de que o senhor Rodenburg vai aprovar sua decisão.";
				link.l1 = "Vá para o inferno você e seu patrão!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Seu idiota, Mongol, chuanzhang! Perdemos tempo demais lidando com seus próprios assuntos em vez de encontrar Jacob van Berg. Ele já foi embora de "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nVocê não conseguiu cumprir a tarefa. Longway não quer mais servir você, nem voltar a vê-lo. Longway tem certeza de que o senhor Rodenburg aprovará sua decisão.";
				link.l1 = "Vá para o inferno você e seu patrão!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Chuanzhang, você já perdeu tempo demais sem resultado. Este não é o seu navio e Longway não é seu carregador. Longway volta para Willemstad\nLongway não vai mais te servir, nem te ver. Longway tem certeza de que o senhor Rodenburg vai aprovar sua decisão.";
				link.l1 = "Vá para o inferno você e seu patrão!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "Chuanzhang, Longway deixou o senhor Rodenburg. Longway nunca mais vai voltar para ele. Você foi gentil com Longway e é um chuanzhang corajoso. Longway quer entrar para sua tripulação como seu criado, Lorde Capitão.";
			link.l1 = "Não como um criado, mas como um oficial! Seja bem-vindo a bordo, amigo!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "Não, obrigado, Longway. Você é um homem livre. Não preciso dos seus serviços.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "Por que parou? Me mate. Longway está cansado, Longway quer morrer. Xing... me perdoe.";
			link.l1 = "Calma aí, chinês. Eu poderia te matar se quisesse, mas preciso falar com você primeiro. Seu destino depende do que você fizer daqui pra frente. Por enquanto, seja bem-vindo ao meu porão de carga!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "Agora podemos conversar sem o barulho de aço batendo nos meus ouvidos. Escute, Longway, preciso de informações e não tenho dúvidas de que você sabe o que eu quero saber. A questão é: vai me contar do jeito fácil ou do difícil?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Vai ficar calado? Muito bem. Vou te fazer uma proposta. Eu poupo sua vida e te deixo em terra firme na próxima parada. Em troca, você me conta onde e por que Lucas Rodenburg te enviou. Fechado?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "Eu sei que você entende inglês, holandês e francês. Também é bom de ouvido. Agora está na hora de começar a falar. Mais cedo ou mais tarde, você vai me contar tudo o que sabe. Sei que vocês chineses se orgulham da sua arte da tortura, mas nós, homens do Ocidente, também fizemos nossos próprios avanços nessa antiga ciência. Alonso aqui é mestre em soltar a língua dos outros. Ele era interrogador da Santa Inquisição em Santiago antes de embarcar no meu navio. Sabe todo tipo de truque que aprendeu com os padres que aperfeiçoaram a arte de arrancar confissões... e nem precisa ser protestante pra isso!";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "Meu talento é desperdiçado com você. Você vai me contar tudo, meu amigo de olhos puxados... Tudo... Mas não vai viver muito depois disso, não vai mesmo. Seu corpo vai sofrer muito depois de encontrar o Alonso. Então a escolha é sua. Ou você me conta toda a verdade e vive, ou me conta toda a verdade e morre em agonia no cavalete. Se contorcendo de dor no cavalete. Entendeu? Não se preocupe, vou garantir que tenha um padre presente para te batizar como cristão, para poupar sua alma pagã das chamas eternas do inferno.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Vejo a dúvida crescendo nos seus olhos escuros. Por que você deveria morrer pelos pecados do seu mestre? Ele merece isso? Rodenburg realmente vale a pena ter sua alma arrancada do seu corpo sofrido?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Longway vai falar. Mas antes, Longway quer ter certeza de que você vai cumprir sua palavra, chuanzhang.";
			link.l1 = "Ha! Palavras sábias! Dou-lhe minha palavra, rapaz.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Desculpe, chuanzhang, sua palavra não basta. Você pega as informações e depois mata Longway! Longway quer garantias.";
			link.l1 = "Você sabe negociar. Que garantias você quer?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "Existe uma pequena ilha, Marie Galante, ao sul de Guadalupe. Cabo Inacessível. Leve Longway até lá e entregue uma arma a ele. Só então Longway vai te contar tudo o que sabe sobre Lucas Rodenburg.";
			link.l1 = "Você não está em posição de negociar comigo, chinês.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Você faria o mesmo se fosse o Longway, chuanzhang. Não seria fácil para seus homens arrancarem palavras de mim, nem mesmo com tortura. Longway não é um branco fraco.";
			link.l1 = "Certo. Fechado. Mas já vou avisando – não tente me passar a perna ou eu mesmo vou te cortar em pedaços. De mil jeitos, e bem devagar... igualzinho fazem seus imperadores. Alonso!";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "Você fala a verdade. Mas lembre-se – eu fui longe demais para você estragar tudo agora. Se tentar me impedir, vou acabar com a sua vida tão facilmente quanto se pisa num inseto.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Já chegamos a Marie Galante, capitão?";
			link.l1 = "Tenha calma, logo estaremos lá.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Você cumpriu sua palavra, chuanzhang. Longway também vai cumprir. Queria saber sobre a missão de Longway?";
			link.l1 = "Sim. Mas permita-me lembrar da sua própria promessa: você vai me contar *tudo* o que sabe.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway se lembra. Ele vai responder qualquer coisa que você perguntar sobre Rodenburg, chuanzhang.";
			link.l1 = "Comece a falar.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng' estava navegando do porto de Willemstad rumo ao norte, em direção às costas de St. Christopher. Em cinco dias, haveria um galeão sob o comando de Peter Stuyvesant. A ordem de Longway era afundar esse navio com o capitão a bordo.";
			link.l1 = "Deus do céu! Rodenburg mandou você matar Stuyvesant? Isso é loucura!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway fala a verdade, capitão. Essa foi a ordem do senhor Rodenburg. Longway não gostou, mas Longway não questiona ordens.";
			link.l1 = "Bem típico de um chinês. Que jogo o seu mestre está jogando?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Not my master anymore, chuanzhang. Longway is not going to return to Mynheer Rodenburg. Rodenburg has seized power in Curacao. Mathias Beck was easy prey; Rodenburg's authority and connections with the commandant were enough to put the governor in jail\nThe only obstacle left is the West India Company director, Mynheer Stuyvesant. Once Stuyvesant is eliminated, Rodenburg will hold every office of power in the Dutch colonies.";
			link.l1 = "Me diga, Longway, o que levou um homem respeitado e poderoso como Rodenburg a tomar atitudes tão radicais contra sua companhia e sua república? E não me venha dizer que foi por causa do sol ou de um acesso de loucura.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway queria ouvir isso de você mesmo, chuanzhang. Foi você quem capturou o navio de correio da Companhia e trouxe a carta para o Rodenburg, certo? O motivo estava naquela carta.";
			link.l1 = "Agora entendo... Parece que há coisas bem impressionantes nos arquivos de John Murdock para deixar Rodenburg assustado o bastante a ponto de se rebelar contra o próprio país.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Quer saber de mais alguma coisa, capitão?";
			link.l1 = "Sim. O que mais o Rodenburg fez?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "O senhor Rodenburg ordenou sua morte. Longway esteve em Caracas antes de caçar Stuyvesant, teve uma reunião com Chuanzhang Jacob e lhe deu ordens.";
			link.l1 = "Capitão Jacob van Berg?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "Você está bem informado. Sim. O chuanzhang Jacob van Berg está caçando você, capitão. Ele vai acabar te encontrando. Ninguém consegue se esconder de van Berg por muito tempo.";
			link.l1 = "Se ele sangra, eu posso matá-lo. Eu vou cuidar do van Berg e do seu tão falado navio fantasma.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Você sabe muito, chuanzhang. Longway não tem nada a acrescentar. Pergunte se ainda tiver algo a perguntar.";
			link.l1 = "Stuyvesant vai estar perto das costas de São Cristóvão?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Sim, chuanzhang. Você poderá encontrar o galeão dele perto da costa desta ilha em cerca de uma semana.";
			link.l1 = "Ótimo! Vamos pegar essa raposa na própria armadilha... Não tenho mais perguntas. Já sei tudo o que queria saber.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Um último conselho, chuanzhang. Você precisa levar a 'Meifeng' se quiser se aproximar do galeão sem ser atacado.";
			link.l1 = "Entendi. Obrigado pela informação.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway está partindo agora. Adeus, chuanzhang.";
			link.l1 = "Boa sorte, meu amigo do Oriente.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Ouvindo atentamente, capitão.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Quais são as ordens, senhor capitão?";
				Link.l1 = ""+npchar.name+", decidi partir para a Europa - para a casa do meu pai. O caminho não será fácil, e não faço ideia de quando poderei voltar. Parece que chegou a hora de nos separarmos. Dificilmente você ficaria me esperando aqui - além disso, não seria seguro.";
				Link.l1.go = "SharlieEpilog_Longway_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, eu vou para a antiga cidade indígena de Tayasal. Vou ser direto: essa vai ser uma jornada realmente perigosa, e também mística – chegaremos lá através do ídolo de teleporte. Você... vem comigo?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, me faça um relatório completo sobre o navio.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Quero que você compre certos produtos toda vez que atracarmos.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Cheguei ao seu comando, Capitão.";
				Link.l2 = "Preciso lhe dar algumas ordens.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ouça minha ordem!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nada. Dispensado!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway nunca foi intendente, chuanzhang. Longway pode te dizer como navegar de Trinidad até Havana e quanto tempo vai levar. Mas Longway nunca conta carga, vendas ou comércio.";
			Link.l1 = "Acho que você tem razão. Seria um desperdício perder um navegador tão talentoso.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Longway não faz negócios com gwailo, chuanzhang. Longway sempre esteve ao leme, não numa loja onde um velho nariz de gancho pechincha pela última peça de oito.";
			link.l1 = "Hum, você tem razão. Provavelmente assustaria os mercadores.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Estou ouvindo.";
			Link.l1 = "Vamos falar sobre abordagens.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Vamos falar sobre o seu navio.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Quero que você deixe meu esquadrão por um tempo e vá buscar sua sorte sozinho.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nada até agora.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Qual é o seu desejo?";
			Link.l1 = "Não aborde navios inimigos. Cuide de si mesmo e da tripulação.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Quero que você aborde os navios inimigos com agressividade.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Qual é o seu desejo?";
			Link.l1 = "Não troque seu navio por outro depois de abordá-lo. Ele vale muito.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando você embarca em navios inimigos, pode reivindicá-los para si, se forem bons o bastante.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Afirmativo.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Vai ser feito.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Sim, senhor.";
			Link.l1 = "Vai ser feito.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Vai ser feito.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Ordens, capitão?";
            Link.l1 = "Fique firme!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Me siga e não fique para trás!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Troque o tipo de munição das suas armas de fogo.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Mude o tipo de munição do seu mosquete.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Troque sua arma principal para combate.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Quero que você atire no inimigo a uma certa distância, Lonway.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Escolhendo o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Selecione o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "No início da luta, você vai usar:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Houve uma mudança de disposição!";
            Link.l1 = "Dispensado.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Houve uma mudança de disposição!";
            Link.l1 = "Dispensado.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "E que distância seria essa? Lembre-se, senhor capitão, não se acerta nada com um mosquete além de vinte metros.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "O que quer dizer, senhor capitão?";
				link.l1 = "Desculpe, às vezes eu esqueço que você não entende piadas direito.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Vou manter minha posição e atirar em qualquer inimigo que se aproxime demais. É isso que você quer?";
				link.l1 = "Sim, exatamente, Lonway.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Isso é longe demais, Lorde Capitão. Você até pode acertar uma multidão, mas mirar em um alvo só - sem chance.";
				link.l1 = "Pode até valer a pena tentar, mas tudo bem.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Entendi, senhor capitão.";
			link.l1 = "Excelente.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway está te seguindo há muito tempo. Longway vai continuar te seguindo como sempre. Longway não vai abandonar seu chuanzhang.";
			link.l1 = "Obrigado, Longway! Fico feliz por ter confiado em você.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quando vamos começar?";
			link.l1 = "Daqui a pouco. Temos que nos preparar para isso.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// Эпилог
		case "SharlieEpilog_Longway_1":
			dialog.text = ""+npchar.name+" pensar que ele é amigo do senhor capitão. Eu pronto para seguir você aonde for, até mesmo para Europa, se for preciso.";
			link.l1 = "Mas você se lembra de como tratam forasteiros como você por aqui, não é? Na Europa é ainda mais complicado. Claro que eu não deixaria ninguém te fazer mal — mas não poderei te proteger de olhares e zombarias. Por isso não posso te dar ordens — você precisa decidir por si mesmo: vai comigo ou...";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = ""+npchar.name+" já acostumar com esse tipo de tratamento. Depois que Chang Shin morrer, senhor capitão foi o único por quem Longway se importar. Eu seguir você e proteger suas costas.";
			link.l1 = "Então... Eu aprecio sua lealdade, meu amigo, e estou sinceramente feliz que estará comigo. Sabe, até te invejo um pouco. Você viu a China, o Caribe — e agora verá a Europa. Poucos tiveram uma jornada tão longa... O nome que Van Marden te deu — acabou sendo profético.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = "...";
			link.l1 = "Partimos em duas semanas. Antes disso, pretendo comemorar essa partida como se deve, na taverna. Você está convidado. E nem pense em recusar.";
			link.l1.go = "SharlieEpilog_Longway_4";
		break;

		case "SharlieEpilog_Longway_4":
			dialog.text = ""+npchar.name+" nem pensar em recusar. Eu vir, senhor capitão.";
			link.l1 = "De outra resposta eu nem esperava. Avisarei quando a farra começar. Primeiro, preciso resolver o resto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Longway_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Longway = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
