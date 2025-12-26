void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Isto é um erro. Entre em contato com os desenvolvedores e explique como e onde você encontrou isso";
					link.l1 = RandSwear()+"Vou avisá-los!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Não tenho autorização para lidar com você. Fale com o nosso oficial.";
					link.l1 = LinkRandPhrase("Claro...","Entendi.","Com certeza!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Se apresente! Quero saber com quem estou falando!";
					link.l1 = "Meu nome é "+GetFullName(PChar)+". O que está acontecendo aqui?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Capitão, seu nome é "+GetFullName(PChar)+", não é?";
					link.l1 = "Sim, você está certo.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "Não. Você me confundiu com outra pessoa.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", muito obrigado! Se não fosse por você, meu destino seria lamentável... Como posso te agradecer?";
					link.l1 = "Não preciso de nada...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Eu não recusaria uma pequena recompensa.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, é ele mesmo... Obrigado, "+GetSexPhrase("companheiro","moça")+", sem a sua ajuda, teríamos passado por maus bocados, não havia como sair da cidade. Aqui, pegue "+FindRussianMoneyString(iMoney)+" e você pode dar o fora. E nós vamos ter uma 'conversa' com o nosso amigo...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, é ele mesmo... Obrigado, "+GetSexPhrase("companheiro","moça")+", sem a sua ajuda, teríamos passado por maus bocados, não havia como sair da cidade. Aqui, pegue "+FindRussianMoneyString(iMoney)+" e você pode dar o fora. Vamos abrir esse traidor imundo agora!";
						link.l1 = "Claro. Até nos encontrarmos de novo, senhores...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "O quê?! Não, eu não vou permitir que você mate um homem, não importa quem ele seja... E eu não preciso do seu maldito dinheiro!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Então... O que temos aqui? Piratas?! Vocês vão ter que nos acompanhar até o gabinete do comandante para um interrogatório...";
					link.l1 = "Não somos piratas, de jeito nenhum! Eu nem conheço esse homem! Ele acabou de alugar e se mudar para este quarto, e eu nem tive tempo de arrumar minhas coisas e sair!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Então, o que você estava dizendo? Tem uma mensagem pra mim?! Estou esperando!";
					link.l1 = "Aqui está...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Ei, você! Isso, você mesmo. Vejo que é um homem decente e de posses.";
					link.l1 = "Não posso dizer o mesmo de você.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Espere! Ei, "+GetSexPhrase("companheiro","moça")+", mostra pra gente o quanto sua bolsa está cheia!";
					link.l1 = "Então, já gastou todo o dinheiro da igreja?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Ei, no barco! Hic... Abre caminho aí – preciso falar com a galera...";
					link.l1 = "Você não está meio tonto, camarada? Vai dormir pra passar.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Ei, capitão! Jogue a âncora!";
					link.l1 = "E por que diabos eu deveria...";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Você não está sendo rude demais!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Saudações! Finalmente, o Senhor atendeu nossas preces e enviou um capitão valente para esta costa esquecida!","Graças à Providência! Agora os urubus daqui não vão se banquetear com nossos ossos podres!");
				link.l1 = "Olá, bom homem, eu sou o Capitão "+GetFullName(PChar)+". Vejo que você está com um belo problema aqui.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Bom homem, tenho meus próprios assuntos para cuidar e não tenho tempo a perder com seus problemas.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Oh, capitão! É realmente uma sorte dos céus que Deus tenha lhe mandado bons ventos e trazido você até este lugar deserto!","Capitão! Graças à Providência que você decidiu lançar âncora nesta costa deserta!");
				link.l1 = "Olá, bom homem, eu sou o Capitão "+GetFullName(pchar)+". Vejo que você está com um problema sério aqui.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Bom homem, tenho meus próprios assuntos para cuidar e não tenho tempo a perder com seus problemas.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Espere, "+GetAddress_Form(pchar)+"! Poderia nos conceder um momento do seu precioso tempo?","Uma dama nobre faria"+GetSexPhrase("ter","s")+" ouça o humilde pedido destes homens indignos?","Nobre senhorita"+GetSexPhrase("ter","s")+", por favor, conceda um momento do seu precioso tempo para falar com este infeliz.");
				link.l1 = LinkRandPhrase("Não tenho tempo para isso.","Cai fora, tenho muito o que fazer sem você.","Me deixe em paz, não tenho tempo pra você.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("O que você quer?","O que você precisa?","Qual é o problema?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Oi, Capitão! Tá interessado em bugigangas indígenas e mercadorias que não se acha em lojas comuns? Ou talvez dinheiro vivo?";
					link.l1 = "Malandros como você normalmente exigem – não oferecem nada. Por que está sendo tão educado, assim do nada?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "Minha pistola costuma falar por mim com canalhas como você!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Estou ouvindo você, capitão. Veio aqui a negócios?";
			link.l1 = "Estou procurando pelo Senhor "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Eu sou o senhor "+pchar.GenQuest.Hold_GenQuest.Name+". A quem devo a honra?","Você o encontrou. O que posso fazer por você?");
			link.l1 = "Eu sou o capitão "+GetFullName(pchar)+", eu queria conversar com você sobre "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "E quem é?";
					link.l1 = "Espera aí... Você é "+pchar.GenQuest.Hold_GenQuest.Name+", e você não sabe sobre "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Caramba! Faz tempo que não ouço falar daquele velho safado. O que aconteceu com ele desta vez?";
					link.l1 = "Desta vez ele está encrencado de verdade... Ele está sendo mantido como prisioneiro e precisa da sua ajuda.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Certo, estou ouvindo.";
					link.l1 = "O navio dele foi atacado por piratas, e agora ele está sendo mantido como prisioneiro. Ele sugeriu que eu procurasse você para tratar do resgate.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "É, fico feliz em saber de um velho amigo. Como ele está?";
					link.l1 = "A situação dele é tão grave que chega a ser difícil de imaginar.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "De fato, sou eu "+pchar.GenQuest.Hold_GenQuest.Name+"! Mas por que eu deveria saber alguma coisa sobre isso "+pchar.GenQuest.Hold_GenQuest.CapName+"?!";
			dialog.text = "Isso mesmo, sou eu "+pchar.GenQuest.Hold_GenQuest.Name+"! Mas o nome "+pchar.GenQuest.Hold_GenQuest.CapName+" não me diz nada."; // belamour gen
			link.l1 = "Me desculpe. Talvez eu tenha me enganado...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Mas que diabos! E como é que eu vou ajudar esse sujeito? Libertar ele matando todos os inimigos dele ou o quê? Ha-ha-ha!";
			link.l1 = "Não, não, isso não é necessário. Você só precisa entregar "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos como resgate.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Que ousadia! E por que eu deveria pagar resgate por ele?! Ele não é meu parente nem meu amigo!";
			link.l1 = "Hmm... Ele me disse que você era a única esperança dele. E também comentou sobre uma dívida sua...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Que sujeito insolente! Só pra você saber, é ele quem me deve dinheiro! Mas isso não é motivo pra eu pagar o resgate dele esperando que ele quite as duas dívidas.","Que canalha! Ele me passou a perna quando dividimos nossos negócios, e agora ainda tem a cara de pau de me pedir resgate!","Essa é boa! Por que eu deveria pagar resgate por ele?! Nem somos tão próximos assim.");
			link.l1 = "Então, posso dizer a ele que você se recusou a pagar o resgate e não reconheceu sua dívida?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Meu Deus! Que dívida é essa de que você está falando? Já te expliquei tudo! E se não tem mais nenhuma pergunta além dessa história boba, então me permita ir embora.";
			link.l1 = "Entendi. Bem, não tenho mais perguntas pra você, mas tenho várias praquele seu amigo.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... E você, pelo que vejo, é quem está mantendo ele preso... Bem, acho que vou ajudá-lo.";
			link.l1 = "Muito bem. O resgate será "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Você me entendeu mal: eu sou membro do conselho da cidade. Nós garantimos o cumprimento da carta.\n"+"Guardas!!! Guardas! Prendam ele sob suspeita de tráfico de escravos e saque de navios de "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "Bem, 'camarada', deixa eu chegar até você...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "O que você está dizendo?! E como posso ajudá-lo?";
			link.l1 = "Ele está sendo mantido como prisioneiro e me pediu para falar com você sobre o resgate dele.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Claro, claro. Vou fazer tudo o que puder. Onde eles estão sendo mantidos? E qual é o valor do resgate?";
			link.l1 = "Os piratas exigem "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos. Preciso entregar o dinheiro no porto, e então seu amigo será libertado.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Aqui está o dinheiro. Felizmente, eu tinha o suficiente comigo.";
			link.l1 = "Sim, isso é realmente uma sorte. Vá até o porto, então, e logo você verá seu companheiro de novo.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Olá, Capitão, desculpe por ainda não ter tido a honra de ser apresentado. Disseram que você estava me procurando.";
			link.l1 = "De fato, se você é o senhor "+pchar.GenQuest.Hold_GenQuest.Name+". Eu sou o capitão "+GetFullName(pchar)+", eu queria falar com você.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "E que tipo de negócio é esse, Capitão "+GetFullName(pchar)+"?";
			link.l1 = "Ouvi dizer que você tem algo do qual não se importaria de se desfazer.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "O que exatamente você está insinuando?";
			link.l1 = "Não seja tão teimoso, meu bom homem, eu sei tudo sobre o seu passado sombrio, e sobre um mapa improvisado mostrando onde está o tesouro"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+" está indicado.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Maldição! Eu sempre soube que aquele canalha"+pchar.GenQuest.Hold_GenQuest.CapName+" ia acabar fofocando mais cedo ou mais tarde! O que eu tinha na cabeça quando fiz esse acordo com ele?";
			link.l1 = "Para de reclamar. Não quero te fazer mal... Só me venda esse mapa e continue levando a vida de sempre.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Se ao menos eu pudesse ter tanta certeza disso... E quanto você vai me oferecer por isso? Com certeza sabe que havia muito ouro no baú. Foram necessários quatro homens para carregá-lo, que Deus os tenha...";
			link.l1 = "Mas "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" já poderia ter reivindicado o tesouro dele...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "É verdade... Tudo bem, estou disposto a te vender por "+pchar.GenQuest.Hold_GenQuest.Sum+" pesos. Eu não ousaria perturbar os mortos de qualquer jeito.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Certo. Temos um acordo.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "Não, meu bom homem, esse pedaço de papel não vale esse dinheiro. Adeus...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "Como isso pode ser possível, capitão?! Deus nunca vai te perdoar por um pecado desses.";
			link.l1 = "Isso cabe a Ele decidir.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Olá, eu sou "+pchar.GenQuest.ShipWreck.Name+", capitão do "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+", meu navio naufragou nos recifes não muito longe da costa."+"Apenas alguns marinheiros de toda a tripulação conseguiram sobreviver. A maré nos arrastou para esta costa desolada. Estávamos famintos e sedentos por "+(5+hrand(7))+" semanas já","Olá, eu sou "+pchar.GenQuest.ShipWreck.Name+", capitão do "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Nosso navio naufragou não muito longe daqui."+"Conseguimos chegar a esta costa depois do naufrágio, mas este lugar parece desabitado. Fomos obrigados a sobreviver de mariscos e frutos de palmeira por "+(5+hrand(7))+" semanas até agora.");
				link.l1 = RandPhraseSimple("E quantos de vocês ainda restam?","E quantos de vocês conseguiram sobreviver?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Oh, capitão, nossas baixas foram realmente terríveis... Olá, eu sou "+pchar.GenQuest.ShipWreck.Name+", capitão e proprietário de "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Ou, devo dizer, ex-capitão e ex-proprietário. "+"Esse desgraçado "+pchar.GenQuest.ShipWreck.BadName+" quem eu contratei em "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" provocou meu bando a se amotinar. No fim, fomos deixados neste lugar esquecido por Deus. Foi assim que aconteceu "+(5+hrand(7))+" semanas atrás.";
				link.l1 = "E depois? Toda a sua tripulação se juntou aos amotinados?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("De toda a tripulação, só "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" survived. Other's have perished; several of them died already here of wounds and fever",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end... either in the deep or in the dunes of this coast.");
			link.l1 = LinkRandPhrase("É, esse é um destino nada invejável. Mas essa é a vida de marinheiro – qualquer um pode acabar no seu lugar.","Entendo... Deus segura todas as vidas, só que Ele está ocupado demais pra lembrar de todo mundo.","De fato. O homem propõe, mas Deus dispõe.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Claro que não! Muitos se recusaram a se juntar aos amotinados, mas esses canalhas tomaram o arsenal, e ainda bem que não resistimos, senão teríamos sido mortos na hora. Muitos já sucumbiram aqui à febre e ao veneno de insetos venenosos, só "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" Sobrevivemos. Graças a Deus, nossas provações finalmente acabaram.";
			link.l1 = RandPhraseSimple("É, isso com certeza foi um baita azar.","Ah, bem, muitas coisas estranhas podem acontecer nesses lugares esquecidos por Deus.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Espere aí, amigo. E como eu vou saber que você não foi deixado aqui como um dos instigadores de um motim?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Capitão, espero que tenha alguns beliches livres no seu navio. Todos nós temos família, e provavelmente estão de luto por nós enquanto conversamos aqui. Seríamos muito gratos a você.","Capitão, estamos completamente desesperados, você é nossa única esperança. Por favor, não nos negue sua ajuda, tire-nos desta terra esquecida por Deus.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Oh... e para onde você gostaria que eu te levasse?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("I am truly sorry, but there isn't a single free hammock, let alone a cabin. The sailors are sleeping on the deck; they can't even get a decent night's rest after their watch...","I would really hate to disappoint you, but the ship is overloaded, and people have to sleep in bad weather. Should there be an outbreak of disease, I will lose half the crew."),RandPhraseSimple("I am truly sorry, but there is absolutely no spare crew space on my ship. I cannot take any more passengers on board.","I'm afraid I must disappoint you, but my ship is overloaded. I fear an epidemic."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Você é um marinheiro experiente e devia saber que a presença de alguém que sobreviveu a um naufrágio é um péssimo presságio. Meus homens vão simplesmente jogar todos vocês no mar.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "O que você está dizendo, "+GetAddress_Form(npchar)+" "+pchar.lastname+"?! Tenha piedade! Eu sou um negociante, conhecido em todo o Caribe! Bem... Acho que eu era, pelo menos. Agora, sem navio ou dinheiro...";
			link.l1 = "Como assim... Aposto que foram vocês os verdadeiros instigadores do motim, e agora receberam o que mereciam.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Mas que canalha é esse "+pchar.GenQuest.ShipWreck.BadName+"! Você vai mesmo deixar ele sair dessa e aceitar o seu destino?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "Para qualquer assentamento de "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "Bem, tenho beliches e redes de sobra. Entre logo no barco.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Temos batalhas pela frente, e eu não sei onde você estará mais seguro, a bordo do meu navio ou neste refúgio acolhedor.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "Para Dunkirk! Minha mãe mora lá...";
					link.l1 = "Você está maluco ou o quê?! Aposto que já levou muita pancada na cabeça...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Onde você quiser, tanto faz pra gente. De qualquer jeito, não temos nada pra te pagar mesmo...";
				link.l1 = "Bem, tenho armários vazios e redes de sobra. Entre logo no barco.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hum... Temos batalhas pela frente, e eu não sei onde você estará mais seguro, a bordo do meu navio ou neste refúgio aconchegante.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "Mas se você recusar, com certeza estará nos condenando à morte! Bem, vamos tentar lutar até o navio, mesmo que isso nos custe a vida!";
					link.l1 = "O quê? Olhem para vocês, mal conseguem ficar de pé...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Pode tentar...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "Mas você não pode simplesmente nos deixar aqui! Sem a sua ajuda, todos nós vamos morrer em breve!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "A única coisa que posso fazer por você é deixar provisões e remédios suficientes, e te dar um barco. Pelo menos você não vai morrer de fome ou sede. Quanto à navegação, não preciso te ensinar isso.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "A única coisa que posso fazer por você é deixar provisões e remédios suficientes e te dar um barco. Pelo menos você não vai morrer de fome ou sede. Quanto a navegar, não preciso te ensinar isso.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Posso deixar remédios, munição, rum e mantimentos suficientes para um mês. Ou eu volto pessoalmente, ou mando alguém vir te buscar.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "Mas se você recusar, com certeza estará nos condenando à morte! Bem, vamos tentar lutar até o navio, mesmo que isso nos custe a vida!";
						link.l1 = "O quê? Olhem pra vocês, mal conseguem ficar de pé...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Pode tentar...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "Mas se você recusar, vai nos condenar à morte! Bem, vamos tentar lutar até o navio, mesmo que isso nos custe a vida!";
							link.l1 = "O quê? Olhem pra vocês mesmos, mal conseguem ficar de pé...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Pode tentar...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Como você pôde fazer isso com a gente?!.. Você não só ignorou o Código do Mar, como também manchou sua honra!";
							link.l1 = "Com certeza não é você quem vai falar da minha honra, seu verme!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "A única coisa que posso fazer por você é deixar provisões e remédios suficientes e te dar um barco. Pelo menos você não vai morrer de fome ou sede. Quanto a navegar, não preciso te ensinar isso.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Você tem razão, não temos chance. Tudo bem, que Deus seja seu juiz, e que cada um receba o que merece.";
			link.l1 = "Bem, eu posso dar conta disso...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Bem... Você não nos deixa outra opção... Vamos rezar para que as tempestades e a sede não tirem nossas vidas antes de chegarmos a algum lugar habitado...";
			link.l1 = "Adeus. Que o Senhor cuide de você...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Aparentemente, não temos escolha... Mas eu lhe peço, Capitão, por favor, volte assim que puder ou envie um navio de expedição.";
			link.l1 = "Vou pensar em alguma coisa. Só espere.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Capitão, por favor, lembre-se que você é nossa única esperança...","Por que você ainda está aqui? Cada minuto passado aqui é insuportável para nós...");
			link.l1 = "Vou fazer tudo o que puder. Adeus...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Adeus, capitão... Precisamos nos preparar para a viagem.","Adeus... E acenda as velas para salvar nossas almas...");
			link.l1 = "Adeus. Que o Senhor cuide de você...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "Como você pôde fazer isso com a gente?! Você não só ignorou o Código do Mar, como também manchou a sua honra!";
			link.l1 = "Com certeza não é você quem vai falar da minha honra, camarão!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Obrigado, capitão! O carregamento não deve demorar muito. Deus, como rezamos para que esse momento chegasse!";
			link.l1 = "Que bom. Espero que suas provações terminem em breve.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Obrigado, capitão! O carregamento não deve demorar muito. Deus, como rezamos para que esse momento chegasse!";
			link.l1 = "Que ótimo. Espero que suas provações terminem em breve.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Vamos lá! Sério, capitão?! A gente tem medo da morte?! Já enganamos ela uma vez, podemos fazer de novo. Só não queremos perder a vida desse jeito. Apodrecer aqui, sozinhos\nA gente se juntaria à sua tripulação com prazer e lutaria sob sua bandeira com coragem. Só não nos deixe aqui...";
			link.l1 = "Vejo que vocês estão dispostos a qualquer coisa só para sair daqui. Mas olhem para si mesmos, que tipo de marinheiros vocês poderiam ser?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "É uma boa ideia. Acho que posso te contratar.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "Não, não, não estou brincando! Por favor, me tire deste matadouro caribenho... me tire deste inferno! Olha, eu sou um homem rico... muito rico. Nem o próprio Papa viu tanto ouro em toda a vida. Eu vou te cobrir de ouro...";
			link.l1 = "Ai meu Deus... Tá bom, entra no barco...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Por que está demorando, capitão? Dê a ordem para levantar âncora.","Desculpe, capitão, mas precisamos nos preparar para zarpar.","Que sorte a nossa você ter decidido vir aqui!");
			link.l1 = "Anda logo. O navio não vai esperar por ninguém.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Capitão, não temos nada a perder. A morte já está nos seguindo... Preferimos morrer lutando do que sermos devorados por coiotes imundos...";
			link.l1 = "Ah, então é um desafio, é isso?! Muito bem, vamos resolver nossa disputa"+GetSexPhrase(", como homens","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Eu juro, capitão, você não vai se arrepender. Seremos os melhores marinheiros de todo o arquipélago.";
			link.l1 = "Ótimo! Entre no barco...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Eu juro, capitão, você não vai se arrepender.","Você fez a escolha certa, capitão.","Capitão, pode ter certeza de que você teve tanta sorte quanto nós!");
			link.l1 = RandPhraseSimple("Espero que sim.","Anda logo. O navio não vai esperar por ninguém.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Capitão, por que ofender pessoas honestas com tanta desconfiança? Olhe só para o rosto deles, você realmente acha que poderiam ser amotinados?";
			link.l1 = "Certo, mas o que eu faço com você agora?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "E o que eu posso fazer? Pelo menos agora estou vivo... e agradeço a Deus por ter escapado! Mas se você me ajudar a recuperar meu navio e se vingar pela minha humilhação, estou disposto a te dar tudo o que esse canalha roubou e escondeu no porão.";
			link.l1 = "Certo, temos um acordo.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Não estamos em posição de dar ordens. Depende de você, só nos leve para qualquer povoado ou aceite a gente na sua tripulação.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Certo, vou deixar você entrar na minha tripulação. Mas nada de brincadeiras! Aqui mando com mão firme!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Eu não vou te levar a lugar nenhum. Já tenho bandidos demais na minha tripulação.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Certo, entre no barco, vou te levar a um lugar.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Pois bem... Você não nos deixa escolha... Vamos rezar para que a Providência tenha piedade de nós e nos permita escapar deste lugar perigoso. Se Deus quiser, ainda podemos chegar a alguma terra habitada...";
			link.l1 = "Adeus. Que o Senhor te proteja...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Muito obrigado, Capitão "+GetFullName(pchar)+"! Você fez tanto por nós que nenhuma gratidão seria suficiente para te retribuir. E embora todos os nossos pertences não valham nem um tostão, permita-me te oferecer este amuleto. Vai ser muito útil para um capitão que vive se metendo em batalhas navais.";
				link.l1 = "Obrigado pelo presente! Este amuleto é realmente muito útil! Até logo, capitão "+pchar.GenQuest.ShipWreck.Name+" e boa sorte pra você nas suas jornadas.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Capitão, muito obrigado. Você fez tanto por nós, que qualquer recompensa seria insignificante diante da nossa gratidão. Por favor, aceite este modesto presente como sinal do nosso reconhecimento.";
				link.l1 = "De verdade, não precisava se incomodar... Você precisa muito mais desse dinheiro do que eu. Mesmo assim, foi muita gentileza sua. Obrigado, e até logo.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Captain, know that there are people who would go to the ends of the earth for you, from now on. It's a pity I have nothing with which to thank you. Still... Please, accept this trinket; I found it in that ill-fated cove. I hope it will bring you luck.";
			link.l1 = "Qualquer um teria feito o mesmo no meu lugar. Adeus.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Capitão, já chegamos a Dunkirk?","Estamos mesmo em Dunkirk, capitão?"),RandPhraseSimple("Capitão, isso é a Europa?","Já chegamos à Europa tão rápido assim?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "A-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Ainda não...","Que Dunkirk? Que Europa? Olhe ao redor!","Meu Deus!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("Mas, capitão, você fez uma promessa!","Como você pôde quebrar sua palavra, capitão?","E quando é que vamos para a Europa?");
			if(rand(100) < 70)
			{
				link.l1 = "Certo. Senhor, reúna seus homens e seus pertences e vá para onde quiser.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Você tem certeza de que precisamos mesmo ir para Dunkirk?","Sabe, meu navio não foi feito para cruzar o oceano.","Capitão, e o que há de errado com o Caribe?"),LinkRandPhrase("Mas eu tinha outros planos...","Por que você quer ir para a Europa, afinal...","Pense em todas aquelas mulheres mulatas tão sedutoras! Você nunca vai encontrar mulheres assim na Europa..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "Mas como?.. Como você ousa?! Que tipo de traição é essa?! Vou te ensinar a cumprir sua palavra!";
			link.l1 = "Bem, você que pediu por isso...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Não! Eu preciso chegar a Dunkirk!","Em vez de me dar aula de geografia, você devia era cumprir com a sua obrigação!"),RandPhraseSimple("Não quero ouvir mais nada sobre isso! Você prometeu me levar para a Europa!","Não, capitão, assim não dá. Estamos indo para a Europa."),"Eu não vou passar o resto dos meus dias vivendo uma vida miserável neste buraco!");
			link.l1 = "Ah, eu não faço ideia de como isso vai acabar...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Viu só! Esse é um homem decente! Europa! Velha e maldita Europa! Sim-sim-sim!\nAh, sim! Você cumpriu sua parte do acordo, e eu também vou cumprir a minha. Aqui, pegue esta metade do mapa. A outra metade estava com meu parceiro. Descanse em paz, ou descanse nas águas? Tanto faz. Foi ele quem me convenceu a entrar nessa aventura.";
			link.l1 = "Espera aí, então você não é marinheiro? Seu camarada era capitão?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Meu Deus!.. Claro que não! Bem, sim, eu não sou marinheiro. E ele foi levado por uma onda enorme quando decidiu navegar mais longe da costa. Então eu assumi o comando e ordenei que entrássemos na enseada... E até que nos saímos bem atravessando os recifes, até que tudo foi decidido por um acidente fatal. O navio bateu num pedaço de rocha e afundou...";
			link.l1 = "Isso sim é uma bela demonstração de incompetência...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Escuta, isso aqui é mesmo Dunkirk? Pensa bem, faz só seis meses e o lugar já mudou completamente\nAqui, pega o mapa, ou melhor, uma parte dele. O tesouro está dentro de uma caverna! Não faço ideia em qual ilha, mas você é um marinheiro experiente, um dia vai encontrar o lugar exato... Te garanto que há riquezas sem fim que pertenciam ao pirata chamado aaarrrrrhg...";
			link.l1 = "Obrigado, meu bom homem. Mesmo que não haja nenhum tesouro, não vou ficar muito chateado. Adeus, e espero sinceramente que nunca mais nos encontremos...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Capitão, que bom que não se esqueceu da gente! Todos nós temos rezado por você!","Capitão, nossa salvação está próxima? Como temos rezado para que ela chegue! Algumas pessoas já começaram a perder a esperança...");
			link.l1 = "Saudações, "+pchar.GenQuest.ShipWreck.Name+"! Como eu poderia deixar meus colegas nesse estado? Para onde?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Saudações, "+pchar.GenQuest.ShipWreck.Name+"! Receio que tenho más notícias para você. Houve uma mudança de planos, e não vou poder levá-lo a bordo.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Não nos importamos para onde vamos, contanto que seja bem longe deste lugar amaldiçoado... Você nos permite começar a embarcar?";
			link.l1 = "Sim, vá em frente com isso. Logo suas provações vão acabar.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Obrigado, capitão. Já estávamos começando a perder as esperanças, mas você realmente nos trouxe de volta à vida.";
			link.l1 = "Não foi nada... Adeus.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "O que diabos você quer de mim?";
			link.l1 = "Cheguei"+GetSexPhrase("","")+" para te mandar saudações de alguém chamado"+pchar.GenQuest.ShipWreck.Name+". Você o conhece?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "É uma pena que eu não tenha estrangulado aquele canalha antes. Pois bem, acho que chegou a hora de pagar pela minha generosidade...";
			link.l1 = "De fato... E o tempo acabou de se esgotar...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Mandou bem, capitão! Então ficou tudo como combinamos? A gente fica com o navio e você com a carga?";
			link.l1 = "Claro. Pegue o navio e faça bom uso dele.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Saúdo você, Capitão "+GetFullName(pchar)+".";
			link.l1 = "E então, o que acha do seu navio?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Heh, está rangendo e gemendo, igualzinho a mim. Acho que nenhum de nós dois tem muito tempo sobrando pra navegar por esses mares...";
			link.l1 = "Boa sorte, então...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Capitão, por favor, ajude a gente a conseguir um navio ou um bote, uma tartana, o que der, tanto faz. Estamos numa situação tão desesperadora que precisamos fugir deste lugar inóspito, mas não podemos aparecer no povoado.";
					link.l1 = "E que tipo de circunstâncias seriam essas?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Capitão, será que poderia nos emprestar algumas centenas de pesos? Não pediríamos, mas estamos realmente precisando muito.";
					link.l1 = "Em apuros, é? Aposto que você só ficou sem rum, e isso sim é um apuro.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Capitão, poderia ter a gentileza de levar nossa humilde companhia até o farol de "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "Olhando pra você, eu não diria que é muito humilde.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Eu não dou esmolas às sextas-feiras.","Não tenho tempo para essas bobagens.","Eu não ajudo estranhos.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Somos fugitivos... de "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+". Logo o antigo mestre vai perceber... e aí estaremos mortos, com certeza.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Então você sabe como lidar com as velas?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "E com o que você vai pagar?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "Não é hora de pensar em rum agora. Faz uma semana que escapamos, estamos escondidos na selva e morrendo de fome.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Bom, suponha que eu te dê dinheiro... e aí? Vai ficar se escondendo até ser encontrado por uma patrulha?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Certo, quanto você precisa?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "Não tenho muito a dizer para gente como você—só cabeças no cepo do carrasco, e nada mais!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "E o que mais podemos fazer? Trabalharíamos como marinheiros sem pensar duas vezes, mas sendo foragidos, quem nos contrataria?";
				link.l1 = "Eu te contrato se souber lidar com as velas e não mostrar nenhum sinal de covardia.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Já chegamos a um acordo com os marinheiros locais. Para sair daqui, só faltam três mil.";
				link.l1 = "Pronto, aqui estão seus três mil, se isso realmente vai te ajudar.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Olha, eu não sei... Esses são problemas seus, e eu não vou te ajudar a resolver isso.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Por favor, capitão, nos contrate, prometo que não vai se arrepender! Já estamos nessa vida de pirata faz "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" no Adriático, até que finalmente foi enforcado e nós, "+pchar.GenQuest.Convict.ConvictQty+" homens foram banidos para este lugar.";
			link.l1 = "Certo. Tem um lugar aqui perto, conhecido como "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+".   Por volta da meia-noite eu te pego lá. Espero mesmo que você não se perca.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Claro, isso vai nos ajudar muito! Vamos zarpar hoje, se o vento estiver a favor e os pescadores não nos deixarem na mão. Obrigado, capitão, e que Deus te ajude...";
				link.l1 = "Boa sorte pra você também.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Isso sim é que é sorte! Jamais imaginamos conseguir o dinheiro tão rápido. Capitão, permita-me lhe entregar um amuleto que pegamos do nosso antigo chefe. Quem sabe ele também lhe traga boa sorte.";
				link.l1 = "Obrigado, isso foi uma atitude decente, com certeza. Boa sorte pra você.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Agora sim, aí está um homem generoso que não tem medo de gastar seu dinheiro, porque sabe como ganhar!\nOntem à noite vimos os contrabandistas locais carregando "+MerPrm.QuestGoodsIdx+". Estava escuro, mas conseguimos distinguir o nome do navio na lateral de um dos barcos, '"+MerPrm.ShipName+"'... e aquele navio está navegando sob a bandeira de "+MerPrm.nation+"Talvez você ache essa informação útil, he-he.";			
				link.l1 = "Hum... Bem, talvez eu faça isso. Adeus para vocês, rastreadores.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Meu Deus, não estamos em posição de fazer exigências. O que puder nos dar, seremos gratos por qualquer coisa.";
			link.l1 = "300 pesos.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 pesos.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3.000 pesos.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Obrigado, capitão, que Deus te proteja...";
			link.l1 = "Boa sorte pra você também.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Agora isso sim é sorte! Jamais imaginamos conseguir o dinheiro tão rápido. Capitão, permita-me lhe entregar um amuleto que pegamos do nosso antigo chefe. Quem sabe ele também lhe traga boa sorte.";
				link.l1 = "Obrigado, isso foi uma atitude decente, com certeza. Boa sorte pra você.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Obrigado, capitão, que Deus te proteja...";
				link.l1 = "Boa sorte pra você também.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "Isso sim é sorte! Nem esperávamos conseguir o dinheiro tão rápido. Capitão, permita-me lhe oferecer um amuleto que pegamos do nosso antigo chefe. Quem sabe ele também lhe traga boa sorte.";
				link.l1 = "Obrigado, isso foi uma atitude decente, com certeza. Boa sorte pra você.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Agora sim, aí está um homem generoso que não tem medo de gastar seu dinheiro, porque sabe muito bem como ganhá-lo!\nOntem à noite vimos os contrabandistas locais carregando "+MerPrm.QuestGoodsIdx+". Estava escuro, mas conseguimos distinguir o nome do navio na lateral de um dos barcos '"+MerPrm.ShipName+"'... e aquele navio está navegando sob a bandeira de "+MerPrm.nation+" Talvez você ache essa informação útil, he-he.";
				link.l1 = "Hmm... Bem, talvez eu faça isso. Adeus para vocês, rastreadores.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "Não traga desgraça pra cima da gente, capitão! Temos um belo amuleto, por favor, aceite como resgate e nos deixe ir...";
				link.l1 = "Entrega logo isso e cai fora enquanto ainda dá tempo.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Agora não temos outra escolha, um homem não morre duas vezes. À última batalha, rapazes!";
				link.l1 = "Agora isso já é outra história!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Bem, com certeza não somos santos, mas também não estamos procurando briga à toa... Somos fugitivos e precisamos sair daqui o quanto antes.";
			link.l1 = "Você tem algo para pagar a passagem?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Ah, entendi... Não, não vou manchar minha reputação por sua causa. Adeus.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Pode deixar! Já estamos bem acostumados com abordagens e essas coisas. Por quase dois anos, nós e o falecido "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" estavam aterrorizando os comerciantes locais, mas infelizmente! Ele foi enforcado, e "+pchar.GenQuest.Convict.ConvictQty+" alguns homens entre nós foram condenados à trabalhos forçados.";
			link.l1 = "Que tal se juntar à minha tripulação? Sou generoso"+GetSexPhrase("","")+", mas não posso te prometer uma vida tranquila.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Sim, pegamos alguma coisa com "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+", então podemos pagar o dobro. Portanto, confio que o preço está acertado. E nem pense em trazer guardas. A traição não será perdoada..."; // belamour gen
			link.l1 = "Certo, me espere na praia "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+". Perto da meia-noite, vai ter um barco esperando por você ... E não quero ver nenhuma gracinha!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "Não, meus amigos. E se eu der o navio para vocês e vocês me apunhalarem pelas costas? Não, não vou ajudar vocês com essa história.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Com muito prazer, "+GetSexPhrase("senhor","errar")+" capitão. Isso a gente conhece bem, e com esse tipo de recomendação mesmo, não vamos ser aceitos na Marinha de qualquer jeito, he-he.";
			link.l1 = "Certo. Tem um lugar aqui perto, conhecido como "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Depois da meia-noite eu vou te buscar lá. Espero mesmo que você não se perca.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Mas, "+GetSexPhrase("senhor","errar")+" capitão, não estamos correndo um risco ainda maior? E se você decidir nos entregar para o comandante?";
			link.l1 = "É verdade... Tudo bem, se eu não estiver lá ao amanhecer, então o acordo está cancelado.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Oh, capitão, estávamos contando com você...";
				link.l1 = "Sem problema. Se você tiver dinheiro, vai conseguir uma passagem. Até logo.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Você é esperto, capitão, isso dá pra ver. Aposto que vai correr direto pro comandante, não é? E você acha mesmo que vai sair impune dessa?";
				link.l1 = "E você planeja me impedir, é isso?! Então vai receber o que merece!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Tem uma coisa. A gente revirou os baús do nosso chefe, mas aí deu uma confusão por causa disso e tivemos que sair na porrada pra escapar. Só "+PChar.GenQuest.Convict.ConvictQty+" homens conseguiram sobreviver.";
			link.l1 = "Dadas as circunstâncias, não posso te oferecer a passagem por menos de "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+" pesos por pessoa.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Vejo que vocês não são covardes. Vão se juntar à minha tripulação?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "E temos escolha? Tudo bem, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"...";
			link.l1 = "Então vá para "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Dat")+". Vou mandar um barco para te buscar depois da meia-noite."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "E por que não? A gente conhece essas coisas, já estamos pirateando com "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" em "+RandPhraseSimple("Gibraltar","Canal da Mancha")+" antes de ficarmos presos aqui.";
			link.l1 = "Certo. Tem um lugar aqui perto, conhecido como "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+".   Por volta da meia-noite eu te pego lá. Espero mesmo que você não se perca.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Ei, capitão, você também já foi pobre, com os bolsos vazios. E agora olha de cima pra gente simples como nós.","Capitão, não é certo tratar o povo assim. Todos nós estamos sob o mesmo Deus."),RandPhraseSimple("Heh, as pessoas estão ficando cada vez mais egoístas hoje em dia. Você vive como se ainda tivesse dois séculos pela frente.","Ah, vejo que você acabou de chegar da Europa, ainda não sentiu o fedor do nosso lixão tropical."));
			link.l1 = LinkRandPhrase("Tá tentando me envergonhar? Vou fazer sua língua ficar uns bons centímetros mais curta!","Está tentando me intimidar? Segure bem o seu chapéu agora!","Você é um filósofo ou o quê? Vou te ensinar a pensar na base da pancada!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Então, capitão? Já conseguiu um navio pra gente?","Saudações, capitão. E então, o que decidiu sobre o nosso acordo?","Olá, capitão. Já estávamos começando a ficar preocupados. Correu tudo bem, imagino?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Tá aqui sua banheira. E não esquece do pagamento. Eu já paguei "+pchar.GenQuest.Convict.ShipPrice+" moedas por isso, então você me deve "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+", exatamente como combinamos.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "Não, mudei de ideia. Procure outra pessoa para te ajudar. Adeus...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Mas é claro! Eles tiraram nossa liberdade, mas não a nossa consciência! Por favor, aceite seu dinheiro junto com nossa imensa gratidão. Você realmente nos ajudou. Se importa se pagarmos em lingotes de prata?";
					link.l1 = "Claro que não. Boa sorte na sua jornada. E reze para que eu não te encontre em alto-mar, porque vou acabar com você rapidinho.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Capitão, sabe, a gente percebeu que dinheiro não é lá tão importante na vida. E, pra ser sincero, agora precisamos dele bem mais do que você. Mas temos algo que roubamos do nosso antigo chefe. Talvez isso te interesse muito mais do que ouro. Quer dar uma olhada?...";
					link.l1 = "É, você tem razão. Isso é realmente incrível. Tudo bem, está feito, temos um acordo. Valeu, até mais.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Por que você precisaria de tanto dinheiro assim, capitão? Você já é rico, e estamos perdidos se não conseguirmos esse navio. Então... vamos simplesmente pegar isso de você. Sem ressentimentos.";
					link.l1 = "Esse foi seu último erro. Sem um navio, você ainda poderia tentar nadar, mas agora vai boiar ou afundar.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Então, capitão? Podemos começar a carregar?","Finalmente! Já estávamos ficando preocupados, achamos que você tinha mudado de ideia.");
			link.l1 = "Desculpe, mudei de planos. Agora você vai ter que procurar outro capitão.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Entra no barco, não tenho muito tempo.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Entra no barco, não tenho muito tempo.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Maldito seja! Com certeza você já mandou uma patrulha atrás da gente?! Você não vai sair impune dessa!";
				link.l1 = "Do que você tá falando?! Tá querendo morrer, é?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Capitão "+GetSexPhrase(", você é um homem de palavra ou não?","?")+" Ou você é só um maldito tagarela... ";
				link.l1 = "É melhor tomar cuidado com o que fala...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Oh, obrigado, "+GetSexPhrase("homem bondoso","moça bonita")+".","Obrigado, capitão, você realmente me salvou da forca.","Agradeço muito por uma viagem tão boa.");
			link.l1 = LinkRandPhrase("Isso tudo é muito bom, mas eu estou esperando o dinheiro.","Chegou a hora de pagar, você sabe.","Dinheiro na mão, como combinamos.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Claro, que perguntas! Aqui está seu dinheiro em barras de ouro, e por favor aceite nossa mais sincera gratidão.";
					link.l1 = "Boa sorte pra você também. Adeus.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Capitão, sabe, a gente pensou que dinheiro não é tão importante assim na vida. E, pra falar a verdade, agora a gente precisa dele bem mais do que você. Mas temos algo que roubamos do nosso antigo chefe. Talvez isso te interesse muito mais do que ouro. Quer dar uma olhada?...";
					link.l1 = "É, você tem razão. Isso é realmente incrível. Tudo bem, está feito, temos um acordo. Obrigado, e até logo.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Por que você precisa de tanto dinheiro? Você já é rico. Você nos ajudou, a gente te ajuda numa outra ocasião.";
					link.l1 = "Não vai ter essa chance. Façam suas preces, canalhas, não tolero dívidas.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Fui enviado aqui por "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" ele mesmo...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" já está te esperando com uma resposta faz algumas horas. Ele me mandou logo depois de você.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Estou te seguindo há um bom tempo, mas você é rápido demais.";
			link.l1 = "E daí?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Melhor me dizer quanto o governador paga pros capangas dele?";
			link.l1 = "Maldição!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "Eu não estava bebendo! Eu estava procurando o contramestre...";
			link.l1 = "Vá agora... Eu aviso "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", que você estava perdido na selva.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "E você é esperto. Reze a Deus para que suas artimanhas não sejam descobertas por "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "Ele não vai saber se você não contar pra ele... E você não vai contar, vai?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Por quê? Claro que vou, e com muito prazer!";
			link.l1 = "Ele vai te enforcar por essa besteira de qualquer jeito. Então vamos parar de perder tempo, e eu vou te ajudar a escapar da forca.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... E como você vai fazer isso?";
			link.l1 = "Eu mesmo vou te matar...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Você tem algum assunto aqui, "+GetSexPhrase("monsieur","mademoiselle")+"?";
			link.l1 = "Não, não, estou aqui a convite da encantadora esposa do governador, apenas admirando esta residência realmente luxuosa.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Tenho um recado de pessoas que você conhece.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Sim. Quero levar você à justiça!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Ah, sim, tive muita sorte de servir numa casa tão bonita.";
			link.l1 = "Não é de se estranhar...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Não se esqueça de dar uma olhada no nosso jardim!";
			link.l1 = "Obrigado, bom homem!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Você não vai escapar impune disso, traidor!";
			link.l1 = "Fique parado, canalha!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Rápido agora! Pegue tudo que for valioso e corra!";
				link.l1 = "Acho que você também deveria correr.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, com licença, preciso me retirar.";
				link.l1 = "Fique parado, canalha!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é "+GetSexPhrase("um ladrão, hein! Guardas, peguem ele","uma ladra, hein! Guardas, peguem ela")+"!","Não acredito! Virei as costas por um segundo e você já está mexendo no meu baú! Peguem o ladrão!","Guardas! Roubo! Parem o ladrão!");
			link.l1 = "Aaaah, diabo!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Oi, "+GetSexPhrase("companheiro","moça")+"! Preparei uma surpresa pra você, acendi o estopim do paiol. Vai explodir pelos ares!","Por que você está parado aí? Tem fogo no paiol de pólvora! Isso vai explodir, e os fogos vão ser vistos até na Europa!");
			link.l1 = RandPhraseSimple("Seu canalha, você não vai me enganar! Lute, seu covarde!","Vejo os ratos abandonando o navio, e você está entre os primeiros?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Você devia correr também, se valoriza sua vida... Mas enfim, não tenho tempo, um barco está me esperando. Aproveite sua pescaria!","Não tenho tempo pra bancar o herói, os caras no barco estão me esperando. Boa pescaria, campeão!");
			link.l1 = RandPhraseSimple("Maldição! Corte as defensas! Soltem as amarras!","Meu Deus, como fomos parar nessa confusão! Abram as comportas! Vamos sair daqui!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "E daí?! Acha que venceu a briga?! Nem pensar. Incendiei o paiol, você não vai sair vivo deste navio.";
			link.l1 = RandPhraseSimple("Seu canalha, você não vai me enganar! Lute, seu covarde!","Vejo os ratos abandonando o navio, e você está entre os primeiros?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Eu tenho um juramento a cumprir, mas isso não quer dizer que eu precise morrer à toa. Desculpe não ter te oferecido um lugar no barco, os marinheiros não iam entender.","Os navios estão presos lado a lado para o abordo, então seu destino está selado. Com licença, mas meu barco está esperando...");
			link.l1 = RandPhraseSimple("Maldição! Corte as defensas! Solte as amarras!","Meu Deus, como fomos parar nessa confusão! Abram as comportas! Vamos sair daqui!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Você venceu! Bem-vindo ao inferno! Incendiei o paiol.","Here you are, my good man! And you are done; I have set a powder room on fire.");
			link.l1 = RandPhraseSimple("Seu canalha, você não vai me enganar! Lute, seu covarde!","Vejo os ratos abandonando o navio, e você está entre os primeiros?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Eu estava te seguindo há um bom tempo. Uma pena ter que sacrificar meu navio, mas a sua cabeça vale por dois novos, de qualquer jeito. Aproveite a pescaria!","Vai sair assim? Cheio de pompa, igual a um príncipe indiano"+GetSexPhrase("ce","cess")+". But I will not come off as a loser; your head is worth far more than my ship. Farewell now, my boat will not wait for too long...");
			link.l1 = RandPhraseSimple("Maldição! Corte as defensas! Soltem as amarras!","Meu Deus, como fomos parar nessa confusão! Abram as comportas! Vamos sair daqui!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Espere um pouco, capitão! Só uma palavrinha.","Espere um pouco, capitão! Acho que isso pode te interessar.");
			link.l1 = LinkRandPhrase("Por que você está falando durante a briga?!","E o que é que eu deveria conversar com um homem morto?","Qual é a sua? Vai fazer um testamento no meu nome?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "Tem um surto de doença a bordo. Perdi um quarto da minha tripulação durante a viagem. Estamos todos condenados...";
			link.l1 = RandPhraseSimple("Seu desgraçado miserável! Por que não avisou que tinha uma desgraça acontecendo no seu navio?!","Esqueceu o código do mar? Você devia ter levantado um sinal no mastro pra avisar que tem um desastre no seu navio!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Íamos morrer de qualquer jeito. Por isso não desistimos, queríamos levar você e seus demônios pro outro mundo junto com a gente! Agora estou completamente satisfeito. Pode terminar sua maldita tarefa.";
			link.l1 = RandPhraseSimple("Você vai pagar por isso!..","Eu gosto da ideia de você morrer primeiro. E eu vou assistir.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Não vou manchar minha lâmina com seu sangue imundo, pode viver, embora... pra quê? Estou tirando minha tripulação daquele velho casco podre.","Você merecia ser enforcado por isso, mas não vai ser preciso agora. Vou tirar meus homens daqui... Pode viver, mas seus dias estão contados...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Olá, capitão, me disseram que você estava me procurando.";
			link.l1 = "Eu estou – se você estiver "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Sou eu mesmo. Alguma coisa importante?";
			link.l1 = "Eu não sei se isso é importante pra você, mas eu trouxe "+pchar.GenQuest.EncGirl.name+". Ela fugiu de casa e agora está te esperando não muito longe da taverna.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Meu Deus... Eu sabia que tudo ia acabar assim... E por que ela fugiu? Ela te contou?";
			link.l1 = "O pai dela quer casar ela com o filho do agiota.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Ah não, não podemos deixar isso acontecer! Capitão, sabe, estou numa situação tão idiota... Eu queria pedir pra você nos levar até "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+" para uma cidade chamada "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", mas agora eu não tenho dinheiro e ainda não consegui um emprego. Tenho uma família rica e uma carreira promissora em "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"...\nEu te garanto, meus pais vão ficar felizes em me ver com uma noiva jovem e vão te recompensar muito bem. Então, você topa?";
			link.l1 = "...Olha, eu tenho planos bem diferentes. Posso te dar um conselho: arrume um trabalho de marinheiro e alugue uma cabine pra sua noiva com o que ganhar. Tem gente que vai pra Europa assim, e esse seu povoado fica a um pulo de passarinho daqui.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Ah, juventude... Você tem ideia do que está me pedindo? Levar uma moça embora dos pais dela sem a bênção deles? ... E que tipo de homem recusaria um pedido desses? Claro que eu topo!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Obrigado, capitão. Vamos lembrar da sua ajuda pelo resto dos nossos dias.";
			link.l1 = "Não foi nada. Espero que tudo acabe bem para você.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Eu prometi te apresentar aos meus pais. Se você tiver um tempinho livre, por favor venha até "+sTemp+", meu pai trabalha lá, e eu vou contar a ele o que você fez por nós. Tenho certeza de que ele vai ficar feliz em te ver.";
			link.l1 = "Certo, eu passo aí quando tiver um tempo. Fiquem bem e cuidem um do outro, vocês dois...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Calma! Calma, capitão! Por favor.","Capitão, por favor, espere, eu imploro...");
			link.l1 = LinkRandPhrase("O quê? Ficou sem fôlego?","Erga sua lâmina, seu covarde!","O que foi? Esqueceu de fazer o testamento?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Espere... Estou ferido e estou fraco demais para continuar lutando... Não estou pedindo piedade, mas tenho assuntos inacabados. Por favor, me prometa que vai realizar o último desejo de um homem moribundo.";
			link.l1 = RandPhraseSimple("Não seja um covarde, capitão, encare a morte como um homem deve!","Capitão, que sentimentalismo é esse? Uma batalha está acontecendo ao nosso redor, então vamos terminar o que começamos.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Fale logo e seja rápido.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Diga "+pchar.GenQuest.CaptainComission.Name+" do povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", que eu não consegui cumprir o pedido dele... antes que eu tivesse tempo de... Que ele me perdoe...";
				link.l1 = RandPhraseSimple("E é só isso?! Tudo bem, eu consigo fazer. Ei, amigo...","Certo, eu aviso ele se tiver tempo. Ei, amigo...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Eu não acho. Não tenho tempo pra essas bobagens. Vamos terminar o que começamos.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Por favor, avise o capitão da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.ShipTypeName+"' "+pchar.GenQuest.CaptainComission.Name+", que ele não deveria mostrar a cara em "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"As autoridades estão cientes das verdadeiras circunstâncias da morte dele "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"... o tempo está acabando, ele vai ser preso... navegando para "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", a viagem vai levar quase quinze dias... ahh... precisamos nos apressar..."; // belamour gen
				link.l1 = RandPhraseSimple("Não posso prometer nada, mas vou tentar quando chegar a hora. Ei, camarada...","Certo, eu aviso ele se tiver tempo. Ei, amigo...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Que crueldade! Espero que você responda por isso.";
			link.l1 = "E por muito mais...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Estou ouvindo você, "+GetAddress_Form(pchar)+".","O que você queria?","Como posso ajudar você?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Você é "+pchar.GenQuest.CaptainComission.Name+"? Tenho negócios com você, Capitão "+pchar.GenQuest.CaptainComission.CapName+" pediu para eu te passar uma informação importante.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "Não, nada...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "Foi mesmo? Certo. Então, o que é que o capitão "+pchar.GenQuest.CaptainComission.CapName+"queria que eu soubesse?";
			link.l1 = "Ele me pediu para te avisar que não vai conseguir atender ao seu pedido.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "Do que você está falando?! Eu conheço ele há anos, é um homem muito honesto. Ele jamais teria dito isso pra você!";
			link.l1 = "Digamos que foi por razões além do controle dele. Em outras palavras - foi o último desejo dele.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ah, isso está totalmente fora de lugar! Tanto tempo desperdiçado\n"+"Capitão, nesse caso, preciso pedir a sua ajuda. Piratas de  "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gen")+" capturaram meu parente "+pchar.GenQuest.CaptainComission.SlaveName+" e estão exigindo um resgate por ele. Você poderia aceitar essa missão? A recompensa deve ser bem generosa.";
				link.l1 = "Infelizmente, eu tenho outros planos.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Vou tentar te ajudar se você explicar com mais detalhes.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ah, isso está completamente fora do lugar! Tanto tempo perdido\nE os baús, como ficam?";
				link.l1 = "Hum... que baús?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Que pena, capitão... É uma lástima que você não queira me ajudar.";
			link.l1 = "Isso não depende da minha vontade, meu amigo. Você precisa entender. Adeus.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Ontem recebi uma carta de "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", em que me avisou que o resgate seria mais alto, e também ameaçou vendê-lo como escravo. O falecido capitão deveria ter avisado "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", que eu concordei com os termos anteriores e fiz um pagamento adiantado. Mas agora entendo por que os piratas aumentaram as exigências.";
			link.l1 = "E o que você está sugerindo?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+GetSexPhrase("companheiro","moça")+", sinto que há algo errado aqui. Estou avisando, isso é muito perigoso e pode ter consequências graves. Capitão "+pchar.GenQuest.CaptainComission.CapName+" tinha três baús cheios de ouro, que ele deveria ter entregue a "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" em "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" como resgate por um homem -  "+pchar.GenQuest.CaptainComission.SlaveName+". E se ele quisesse que você viesse até nós, ele não teria esquecido de te contar sobre os baús.";
			link.l1 = "Enquanto dizia suas últimas palavras, parecia que não tinha terminado a frase. Eu esperava que você me contasse mais.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Não me resta outra opção... Já consegui juntar a quantia necessária, 150.000 pesos. Peço que entregue para "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" e traga meu parente aqui. Eu vou te pagar 40.000 assim que estiver feito.";
			link.l1 = "Certo, estou pronto.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Infelizmente, tenho outros planos.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Então pegue o dinheiro e que nosso Senhor te abençoe. Mas, por favor, seja rápido. Eu tenho medo que "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" não vou esperar e vou vender o pobre coitado como escravo.";
			link.l1 = "Espere por mim aqui. Acho que não vai demorar muito.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "Não importa\nAs pessoas que juntaram o resgate não vão se importar. Tudo o que querem é o resultado: vivo e inteiro - "+pchar.GenQuest.CaptainComission.SlaveName+". Então não perca tempo.";
			link.l1 = "E se eu recusar?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "Na verdade, não preciso do seu consentimento. Só estou te avisando que, se você não entregar "+pchar.GenQuest.CaptainComission.SlaveName+" vivo e bem na taverna, vou mandar caçadores de recompensa atrás de você...";
			link.l1 = "Hmm... Isso é sério. E se eu fizer?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "Então vamos discutir isso mais adiante.";
			link.l1 = "Certo... Vamos ver como isso vai acabar.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Olá, Capitão "+GetFullName(pchar)+". Alguma novidade?","Então, capitão, já entregou o resgate?","Olá, espero que tenha vindo com boas notícias?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Infelizmente, meus planos mudaram, então vou ter que desfazer nosso acordo.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Ainda não. Ainda estou ocupado com isso.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Ah, que bom ver você, capitão "+GetFullName(pchar)+". Alguma novidade boa?","Então, capitão, já resgatou nosso amigo sofredor?","Que bom ver você vivo e bem, capitão. Qual é a situação do nosso assunto em comum?");
					link.l1 = "Por enquanto, nenhuma novidade, mas estou cuidando disso.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Escuta, amigo, por que você está tentando me responsabilizar por esse acordo?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Olá, Capitão "+GetFullName(pchar)+". Alguma novidade?","Então, capitão, já entregou o resgate?","Olá, espero que tenha vindo com boas notícias?");
					link.l1 = "Sim. Seu pedido foi atendido, "+pchar.GenQuest.CaptainComission.SlaveName+" está a bordo do meu navio e está se preparando para desembarcar.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, que bom ver você, capitão "+GetFullName(pchar)+". Alguma novidade boa?","Então, capitão, já resgatou nosso amigo sofredor?","Bom ver que está vivo e bem, capitão. Qual é a situação do nosso assunto em comum?");	
					link.l1 = "Trouxe o homem de quem falamos. Ele está a bordo do meu navio.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Olá, Capitão "+GetFullName(pchar)+". Alguma novidade?","Então, capitão, já entregou o resgate?","Olá, espero que você tenha vindo com boas notícias?");
					link.l1 = "Saudações, "+pchar.GenQuest.CaptainComission.Name+", tenho que te decepcionar.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, que bom te ver, capitão "+GetFullName(pchar)+". Alguma novidade boa?","Então, capitão, você já resgatou nosso amigo que está sofrendo?","Bom ver que está vivo e bem, capitão. Como anda o nosso assunto em comum?");
					link.l1 = "O homem por quem você estava intercedendo está morto.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Obrigado, capitão, você fez um grande favor à nossa família. Aqui está sua recompensa... São três baús – isso dá exatamente 40.000 pesos. Por favor, me desculpe, preciso vê-lo agora.";
			link.l1 = "Claro, tenham uma boa reunião e boa sorte para vocês dois.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Eu entendo perfeitamente a sua impaciência, mas surgiram imprevistos que me obrigaram a arcar com custos extras.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eu não entendo... Nós já combinamos o valor do seu pagamento, não foi?";
			link.l1 = "Nós temos, mas em vez de 150.000 pesos fui obrigado a pagar 200.000, sem falar na viagem até Barbados.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Capitão, isso é só resultado da sua própria preguiça. Os piratas não me fizeram nenhuma exigência extra. Que sujeito estranho, tentando lucrar com o sofrimento dos outros?";
			link.l1 = "Certo, vejo que é inútil tentar te explicar qualquer coisa...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Excelente! E você ainda duvidava que a gente ia se dar bem juntos.";
			link.l1 = "Mas eu tive que gastar muito com esse negócio.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Eu sei, eu sei... Mas isso também é culpa sua. Como você conseguiu afundar três baús de ouro, que tivemos que praticamente arrancar do tesouro, só para que "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" poderia ter um especialista assim "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "Saiba que não vou entregá-lo a você sem uma compensação adequada.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Bem, você é um homem inteligente, certamente entende que já é tarde demais para negociar. Poderíamos ter tomado seu navio junto com a carga.\nMas a compensação foi providenciada antecipadamente. Portanto, o governo de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" parabeniza você pela operação bem-sucedida e lhe entrega este valioso presente e uma modesta recompensa.";
			link.l1 = "Hmm... Bem, ainda é melhor do que nada. Leve seu precioso especialista.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Ah, que pena! Já perdi tempo demais. Você realmente me decepcionou, capitão!";
			link.l1 = "Eu entendo, mas as circunstâncias estavam fora do nosso controle. Aqui está o seu dinheiro.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Você poderia se apressar, por favor? Temo que os piratas mudem os termos do acordo mais uma vez.";
			link.l1 = "Não se preocupe, a gente dá um jeito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "Espero que você saiba que está correndo contra o tempo?";
			link.l1 = "De novo! Já estou cuidando disso. Tenha paciência.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Deus nos proteja! Sem pressão, só uma ajudinha de um humilde puritano\nA culpa é sua. Você matou o capitão "+pchar.GenQuest.CaptainComission.CapName+", perdemos nosso ouro e falhamos em resgatar um homem muito valioso. Agora é um baita problema e responsabilidade sua. Nem pense que está perdoado... Você vai pagar por tudo.";
			link.l1 = "Vai se ferrar!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Oi, queria alguma coisa?";
			link.l1 = "Posso ver o dono desta plantação?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Ele não está aqui, está procurando um escravo fugitivo, Blade ou Blood, não lembro... E eu sou o administrador local "+npchar.name+" e estou autorizado a resolver tudo enquanto o chefe está ausente.";
			link.l1 = "É mesmo? Que bom... E vender escravos, também faz parte do seu negócio?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Claro. Quantos você quer comprar?";
			link.l1 = "Só um.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Tem certeza de que precisa só de um escravo?";
			link.l1 = "Claro que sim, eu sou. O nome dele é "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Mas certamente você entende que o preço de um único escravo será mais alto comparado ao preço de um escravo em um lote maior?";
				link.l1 = "Claro que sim. Pode dizer o preço?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hum... Espero que você saiba por quem está intercedendo?";
					link.l1 = "O que você quer dizer?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Ah, aquele vagabundo. Eu não daria nem um tostão por ele. Desde que chegou aqui, nunca fez um trabalho de verdade. Não faço ideia de por que o coronel gasta dinheiro com esses condenados do estado. Agora, os negros são outra história. São trabalhadores excelentes, está no sangue deles serem fortes e obedientes. E pode acreditar, eles fazem qualquer serviço. Colheita de cana ou mordomia — fazem tão bem quanto qualquer um, é só dar um pouco de 'convencimento'...";
					link.l1 = "My friend, I couldn't care less about your black men. I'm only interested in that loafer you mentioned; he won't live long anyway. I need him as cannon fodder, and I'll pay more for him.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Certo, certo. Deixe-me ver o preço\nAh! 150.000 pesos.";
			link.l1 = "Que diabos...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "O preço deve estar na lista de preços. Aqui. Sabe, eu não entendo muito bem. Outros escravos são vendidos por preços razoáveis, mas aquele está sendo vendido por uma fortuna...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Acho que entendi o que está acontecendo aqui... Tudo bem, aqui está o dinheiro, e vou levá-lo comigo.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... Mas eu não estou pagando resgate por um refém, quero comprar um escravo comum. Você não acha que daria pra comprar um navio decente, totalmente equipado, por essa quantia?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Esse não é um escravo comum. O coronel Bishop até mandou que ele fosse vigiado.";
			link.l1 = "Então eu nem posso comprá-lo?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Claro que pode. O Coronel colocou um preço nele – 200.000 pesos, de acordo com a tabela de recompensas.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Caramba! Bom, com certeza aquele coronel deve saber muito bem que tipo de pessoa é esse escravo...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... Mas eu não estou pagando resgate por um refém, quero comprar um escravo comum. Não acha que por esse valor dá pra comprar um navio decente, pronto pra navegar?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ah, sim. Com licença. Deixe-me ver os preços que o Bispo deixou.\nAhá, aqui está. Bem. Oh!.. 150.000 pesos!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Aparentemente, isso é algum tipo de engano. Você certamente percebe que nenhum escravo poderia custar tanto assim. Suponho que colocaram um zero a mais, e a quantia deveria ser 15.000 pesos. E ainda assim é demais, considerando que ele é um vagabundo e um idiota.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... Mas eu não estou pagando resgate por um refém, quero comprar um escravo comum. Não acha que por essa quantia daria pra comprar um navio decente, totalmente equipado?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Ótimo! Que maravilha! Eles vão trazê-lo aqui imediatamente... É... Talvez um chá?";
			link.l1 = "Não, obrigado... Mande lembranças ao Coronel Bishop...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "E de quem, posso saber?";
			link.l1 = "Mmm... Deixa pra lá, não se incomode. Adeus.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Me desculpe, mas não posso fazer nada. Aqui está a lista de preços.";
			link.l1 = "Ah, chega disso, 'lista de preços, lista de preços...' Nenhum de vocês consegue decidir a coisa mais simples sem o Bishop. Diz pra ele... Quer saber, deixa pra lá, não diz nada.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Então você não vai comprar aquele escravo.";
			link.l1 = "Não. Adeus.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Eu não sei nada sobre isso. Só recebi instruções específicas sobre a venda daquele escravo em particular.";
			link.l1 = "Besteira... Tá bom, tanto faz. Aqui está o dinheiro. Traga o escravo.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Claro. Ele será trazido aqui num instante.";
			link.l1 = "Adeus.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Sim, talvez você esteja certo. Deve ser um engano.";
			link.l1 = "Bem, se já acertamos o preço, posso levá-lo comigo agora?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Sim, claro. Ele será trazido aqui em um instante.";
			link.l1 = "Muito bem. Aqui está o seu dinheiro... Adeus.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Quer um pouco de chá, capitão?";
			link.l1 = "Não, obrigado.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Você decidiu comprá-lo?";
			link.l1 = "Não. Adeus.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Olá, capitão. Como posso ajudar? Mal posso acreditar que esse tormento finalmente acabou.";
				link.l1 = "Você deveria agradecer não a mim, mas sim ao seu parente "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Ele já conseguiu o resgate.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Olá, capitão. Disseram que você pagou o resgate por mim. Preciso te agradecer por isso, embora eu saiba que você só foi o mensageiro.";
				link.l1 = "Você não parece tão feliz com a sua liberdade recém-recuperada. Está preocupado com alguma coisa?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Por favor, se não atrapalhar muito seus planos, me leve até ele. Gostaria de agradecê-lo pessoalmente.";
			link.l1 = "Claro, eu vou. Venha, vou te levar até o navio.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Para ter certeza da minha liberdade, preciso saber os nomes de quem pagou por ela.";
			link.l1 = "Bem, fui eu quem pagou, embora não tenha sido por vontade própria.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Então, minhas suspeitas estavam certas. Você foi obrigado a fazer isso por "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Sim, é "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Entendi. Não faço ideia do que te prometeram, mas é o seguinte: me leve até a taverna de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", lá eu estarei realmente seguro. Em troca, vou compartilhar algumas informações que possuo com você.";
			link.l1 = "Tudo bem, ainda mais porque eles não prometeram nada até agora. Venha comigo, vou te levar até o meu navio.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "Não vou arriscar me meter em encrenca por causa de uma informação duvidosa.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Infelizmente, não posso te contar isso agora. Isso pode trazer problemas para nós dois.";
			link.l1 = "Ainda mais agora... Me siga, e nada de besteira, por favor. Considere-se preso de novo.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "O quê?! Os piratas mudaram o acordo de novo? Mas eu não posso tirar mais dinheiro do negócio! Desse jeito, logo vou à falência!";
			link.l1 = "Não... Seu parente morreu nas plantações de Barbados durante uma tentativa de fuga que não deu certo.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Oh... Estou completamente arrasado... Como isso aconteceu?";
			link.l1 = "Os piratas não esperaram pelo resgate e o venderam como escravo. Fui atrás dele até Barbados, mas não consegui salvá-lo...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Jesus! O que está acontecendo?\nMuito bem, capitão, obrigado por participar. E por favor, devolva o dinheiro que eu lhe dei.";
			link.l1 = "Minhas despesas superaram todas as expectativas, então vou ficar com o seu dinheiro... Adeus.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Claro, pode pegar... Desculpe por não ter conseguido te ajudar... Adeus.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "Que pena. Você não faz ideia do quão ruim isso realmente é...";
			link.l1 = "Não há nada que eu possa fazer sobre isso. Até fico aliviado que tudo tenha acontecido assim. Adeus.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Beba... Capitão, traga um pouco de água...";
			link.l1 = "Ei, camarada, você não é "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "É... Sou eu mesmo...";
			link.l1 = "Escuta! Se não quiser morrer aqui feito um peixe encalhado, se controla e presta atenção em mim. Sabe onde fica o Farol de Barbados?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Eu aceito...";
			link.l1 = "Assim que tiver uma oportunidade, corra para lá. Vou tentar arranjar essa chance para você.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Pode perguntar, capitão, mas seja rápido, estou de serviço.","Fale, mas seja rápido e não me incomode com bobagens.");
			link.l1 = RandPhraseSimple("Você pode me dizer como faço para encontrar um certo escravo? O nome dele é "+pchar.GenQuest.CaptainComission.SlaveName+".","Em algum lugar desta plantação deve haver um escravo chamado "+pchar.GenQuest.CaptainComission.SlaveName+". Você pode me dizer como eu poderia falar com ele?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Hoje ele está sendo punido e sob vigilância.";
			link.l1 = "Valeu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Obrigado... Capitão, você salvou minha vida...";
			link.l1 = "Corra até o farol em Barbados e me espere lá.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Capitão, como posso te agradecer? Ainda não consigo acreditar que esse tormento finalmente acabou.";
				link.l1 = "Já fui agradecido pelo seu parente "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Eu ajo conforme as instruções dele.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Obrigado, capitão. Não sei a mando de quem você está agindo, mas até uma liberdade miserável é melhor do que uma boa escravidão.";
				link.l1 = "O que você quer dizer?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Se não atrapalhar muito seus planos, por favor, me leve até ele. Estou simplesmente cansado de tudo isso.";
			link.l1 = "Claro que eu vou... se a gente conseguir sair daqui vivos.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "E posso saber os nomes de quem pagou pela minha liberdade?";
			link.l1 = "Bem, na verdade, não me pagaram. Não me deixaram escolha.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Então, minhas suspeitas estavam certas. Você foi obrigado a fazer isso por "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Sim, é "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Eu não faço ideia do que te prometeram, mas é o seguinte: me leve até a taverna de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", lá eu estarei realmente seguro. Em troca, vou compartilhar algumas informações que possuo com você.";
			link.l1 = "Tudo bem, ainda mais porque eles não prometeram nada até agora. Venha comigo, vou te levar até meu navio.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Não vou arriscar me meter em encrenca por causa de uma informação duvidosa.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Infelizmente, não posso revelar isso para você agora. Isso poderia trazer problemas para nós dois.";
			link.l1 = "Mais ainda... Me siga e nada de besteira, por favor. Considere-se preso de novo.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Obrigado, capitão. Agora estou finalmente a salvo. Não vou lhe oferecer dinheiro, pois tenho certeza de que o conhecimento e seu uso habilidoso valem muito mais do que qualquer metal perecível.";
			link.l1 = "Estou esperando pela informação";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "A questão é que eu sou um cientista, um especialista em "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" e "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" já vinha me oferecendo cooperação há um bom tempo,"+"mas eu sou engenheiro militar e cumpro meus juramentos de lealdade. Tentaram me sequestrar, mas os verdadeiros problemas começaram quando os piratas descobriram minha verdadeira identidade e importância\n"+"In the end, they managed to capture me, yet gold was all they wanted; they never needed my knowledge. My friends and enemies failed to ransom me in time, and I was sold to the plantations. You know the rest.";
			link.l1 = "É, desgraça para a esperteza, como dizem, de fato.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "Bom, pode-se dizer que sim. Então, se você prestar atenção no que eu te disser, vai se tornar muito mais habilidoso na arte de "+sTemp;
			link.l1 = "Muito obrigado, essa informação é realmente muito útil.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Bem, adeus, e obrigado por tudo.";
			link.l1 = "Obrigado pra você também. Adeus, e tenta não ser pego da próxima vez.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Ahoy, eu sou o Capitão "+GetFullName(NPChar)+", o que te traz ao convés do meu navio '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'?","Ah, fico sempre feliz em receber visitas no meu navio. Capitão "+GetFullName(NPChar)+" às suas ordens.");
			link.l1 = "Olá, eu sou o capitão "+GetFullName(pchar)+", agindo em nome de certo capitão "+pchar.GenQuest.CaptainComission.CapName+". Ele me pediu para avisar que você será preso em "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". As autoridades sabem sobre "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "O que diabos você está fazendo aqui? Já combinamos tudo! Volte para o seu navio!";
			link.l2 = "Uhh... É, claro!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ah, que pena! Deixe-me pensar\nE onde está o capitão "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Ele morreu.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Maldição! As coisas só estão piorando... Escuta, "+GetFullName(pchar)+", eu não estou pronto para encarar uma reviravolta dessas, Capitão "+pchar.GenQuest.CaptainComission.CapName+" e eu combinamos de nos encontrar em "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". O plano era carregar alguma mercadoria no navio dele. Agora que o capitão está morto, não posso aparecer no povoado\nParece que não me resta outra opção a não ser te pedir um favor.";
			link.l1 = "Meu consentimento vai depender do tipo de ajuda que você precisa.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Me ajude com alguns homens e botes. Preciso que a carga seja levada daqui "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+". Pode ficar com a parte do capitão falecido da carga.";
			link.l1 = "Hmm... Pelo visto, você se meteu em algo maior do que consegue lidar. Preciso de mais informações.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Infelizmente, não estou em posição de perder tempo com isso.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Certo, vou te contar os detalhes\n"+"Durante uma das minhas patrulhas de rotina, encontrei uma embarcação hasteando a bandeira de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Eles ignoraram minhas ordens de se render."+"Quando, depois de uma breve perseguição, nós alcançamos "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' e então eles hastearam a bandeira negra. O forte estava bem distante, então tivemos que lutar sozinhos. Eles destruíram nosso gurupés, por isso não conseguimos evitar o abordo.\n"+"Foi por pouco, mas conseguimos matar todos eles  graças à Santa Maria e a uma unidade de mosqueteiros. Imagine a nossa alegria quando descobrimos que "+sTemp+" estava cheio de. "+"Decidimos que esta é uma recompensa justa pelas nossas feridas e pelas mortes dos nossos companheiros\nJá estava escuro, nós pegamos "+sTemp+" até a baía mais próxima e escondemos a carga em terra. Depois, explodimos "+sTemp+" e eu informei sobre o navio pirata afundado. Claro, não falei nada sobre a carga.";
			link.l1 = "Aparentemente, alguém ainda acabou soltando a língua...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Que pena, capitão... É uma lástima que você não queira me ajudar.";
			link.l1 = "Isso não depende da minha vontade, meu caro. Você precisa entender. Adeus.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Não acho que tenham sido meus homens. Muito provavelmente, o dono da carga está ansioso para aliviar a dor da perda\nE então? Posso contar com sua ajuda?";
			link.l1 = "Sim, parece bom.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "Não, meu amigo. Primeiro: não sei quanto da carga vai acabar no meu porão. E segundo: não há garantia de que as autoridades ainda não encontraram e levaram tudo, deixando uma emboscada no esconderijo.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Vamos nos encontrar em "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" então, logo depois da meia-noite. Minha posição atual exige discrição. Precisamos evitar as patrulhas."; // belamour gen
			link.l1 = "Certo, me espere lá.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Que pena, mas você não me deixa escolha. Um navio só não é suficiente para levar toda a carga. Arrisquei minha carreira e minha vida por isso. Com certeza, sua tripulação vai ficar feliz em me ajudar em troca de uma parte justa.";
			link.l1 = "E o que você está sugerindo?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Vou tomar seu navio e deixar você aqui "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "Não acredito que você vá conseguir. Vou voltar para o meu navio, nem que eu tenha que derrubar toda a sua tripulação.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Parece que não tenho escolha. Bem, vou me submeter à violência...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Capitão, precisamos nos apressar. Temo que uma patrulha possa nos ver.";
			link.l1 = "Certo, vamos logo.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Capitão, ordene o lançamento de todos os botes salva-vidas. Teremos que fazer várias viagens, e receio que uma patrulha possa aparecer na enseada. ";
			link.l1 = "Não se preocupe, tudo deve ficar bem. Os barcos já estão chegando à praia.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Ah, droga. Agora temos companhia...";
			link.l1 = "É verdade, basta falar de um tolo que ele aparece na hora...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Capitão, estamos procurando um criminoso de guerra "+pchar.GenQuest.CaptainComission.Name+", que escondeu uma carga valiosa das autoridades. Seus documentos, por favor.";
			link.l1 = "Que documentos, oficial? Nós desembarcamos só para reabastecer nossa água fresca.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "E aqui está ele, "+pchar.GenQuest.CaptainComission.Name+"  entregue suas armas e me siga, vocês dois!";
			link.l1 = "Essa foi uma péssima hora pra isso, oficial...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Precisamos nos apressar antes que cheguem reforços. A carga está quase pronta, e a sua parte é "+pchar.GenQuest.CaptainComission.GoodsQty+" unidades de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".";
			link.l1 = "Excelente. Hora de partir agora. Foi um prazer fazer negócios com você.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "E só mais um pedido. As autoridades com certeza vão nos perseguir, você poderia escoltar meu navio até "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", que fica em "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "Não, meu amigo, daqui pra frente é cada um por si. Adeus...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Claro, eu posso fazer isso por uma boa recompensa.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Claro. Pela escolta, estou disposto a pagar  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" pesos. Mas tem mais uma condição: não pode levar mais do que "+pchar.GenQuest.CaptainComission.iDay+" dias. Isso é importante.";	
			link.l1 = "Fechado. Vamos partir imediatamente.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Capitão, estamos perdendo tempo. Eles podem nos encontrar a qualquer momento.","Capitão, estamos correndo contra o tempo. Não esqueça que estão me procurando.","Capitão, não podemos demorar. Meu navio é grande demais para passar despercebido pela patrulha.");
			link.l1 = LinkRandPhrase("Sim, você está certo. Temos que nos apressar.","Então entrem logo nos botes, sem mais demora.","É isso... Reúna seus homens. Vamos embora.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Capitão, preciso falar com meus homens.";
			link.l1 = "Pode ir.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Saúdo você, Capitão "+pchar.CaptainComission.Name+". Então, trouxe toda a carga? E onde está o capitão "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" morreu. Eu tive que perguntar "+NPCharSexPhrase(sld,"esse cavalheiro","essa moça")+" para ajudar. Vou te apresentar. Este é o Capitão "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "E   "+NPCharSexPhrase(sld,"Quem é ele? Ele é","Quem é ela? Ela é")+"   está ciente dos nossos assuntos?";
			link.l1 = "Geralmente, sim. Mas tem um problema -"+NPCharSexPhrase(sld,"ele tem certeza","ela tem certeza")+", que metade da carga pertence a "+NPCharSexPhrase(sld,"ele","ela")+". Precisamos convencer "+NPCharSexPhrase(sld,"ele","ela")+", que não é bem assim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Meu amigo "+GetFullName(pchar)+", você já ouviu tudo o que precisava saber. Precisamos acessar seu porão.";
			link.l1 = "E você acha que meus rapazes vão ficar parados assistindo enquanto uns moleques esvaziam o porão deles?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Você tem razão. Dinheiro, digamos, na quantia de "+pchar.GenQuest.CaptainComission.GoodsSum+" pesos, vai nos poupar de ter que enfrentar sua tripulação. Lembre-se que isso cobre metade da nossa carga, então está tudo justo. Se concordar com isso, ninguém vai se machucar.";
			link.l1 = "E se eu recusar?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "Nesse caso, a violência é inevitável. Você será a primeira vítima e vai encontrar paz nesse refúgio acolhedor, enquanto sua tripulação não poderá vir em seu socorro... O que acha disso?";
			link.l1 = "Você não me deixa escolha. Então, vou matar todos vocês.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Eu acho que não tenho escolha. Tudo bem, aqui está o seu dinheiro.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Bem, essa é uma decisão apropriada para "+GetSexPhrase("um cavalheiro nobre","uma dama valente")+".";
			link.l1 = "Chega de filosofar! Vamos ao que interessa!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Uma decisão sábia. Boa sorte pra você.";
			link.l1 = "Que você engasgue com isso...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Capitão "+GetFullName(pchar)+", estamos atrasados. Espero que entenda que agora você não tem mais direito à recompensa.";
			link.l1 = "Claro que sim. Já ganhei um bom dinheiro, graças a você. Até logo...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Você compraria um pouco de rum para um velho soldado que sofreu muito nas batalhas pela glória da Coroa?";
			link.l1 = "Barman! Sirva um pouco de rum pra gente!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Oh, obrigado, "+GetAddress_Form(pchar)+", muito gentil da sua parte ajudar um aleijado que tinha perdido completamente a memória...";
			link.l1 = "Completamente, é isso que você diz?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Com certeza, senhorita"+GetSexPhrase("ter","s")+" capitão... de verdade. Não me lembro de nada, só de uma bala de canhão voando direto na minha cabeça. Olha o buraco que fez, acho que toda minha memória deve ter escapado por ele.";
			link.l1 = "Amigo, guarde essas histórias patéticas pra donas de casa. Já vi gente levar tiro de canhão à queima-roupa, perder a cabeça e a memória de uma vez... E você aqui, falando de bala de corrente imaginária. Vamos falar do capitão, vai "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Ah, bem, você sabe. Tenho que ganhar a vida de algum jeito. Quanto ao capitão "+pchar.GenQuest.CaptainComission.Name+", não ganho nada fofocando... Se eu cobrasse cem moedas por cada pergunta sobre ele, já teria mais ouro do que o governador arrecada dos súditos em um ano... ";
			link.l1 = "E você já tentou vender a carga que aquele capitão escondeu?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "O quê? Outro farejador? Já falei, não me lembro de nenhum capitão "+pchar.GenQuest.CaptainComission.Name+"! Estou com uma concussão, e tenho o atestado do médico pra provar! O que mais você quer?!";
			link.l1 = "Epa, calma aí. Sabe... Ele chegou tarde demais. Capitão "+pchar.GenQuest.CaptainComission.CapName+" pediu para eu dizer que "+pchar.GenQuest.CaptainComission.Name+" não deveria mostrar o rosto naquele assentamento, as autoridades já sabem das circunstâncias da destruição de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+", e ele será preso.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Ufa. Você devia ter dito isso logo de cara e não ficado enrolando. Fui eu quem pediu ao capitão "+pchar.GenQuest.CaptainComission.CapName+" interceptar nosso navio quando ela voltar. "+"Foi levado para o cais logo depois daquela maldita briga. O que aquele desgraçado daquele pirata estava fazendo lá com a mercadoria dele?! Tantos rapazes morreram por causa dele.";
			link.l1 = "E como você conseguiu sobreviver?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Por engano. Pra ser sincero, por um maldito erro meu. Não fui rápido o bastante, então nosso bote não conseguiu sair da área de perigo. Só eu acabei me dando mal. Fui atingido por uns destroços e jogado na água. Nem lembro direito como consegui chegar à praia.";
			link.l1 = "E como você conseguiu escapar da investigação?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Eu disse a eles que tinha me ferido durante o abordo e não sabia nada sobre nenhuma carga. Também fingi ser meio lerdo, sabe, tinha acabado de me recuperar, bem antes da chegada de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+".   Não conseguia me mexer direito, minha coordenação estava péssima.";
			link.l1 = "Ei, mas quem foi que deixou escapar o segredo sobre a carga, afinal?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "Os piratas enviaram uma carta ao governador, supostamente em nome do mercador ferido. Eles decidiram se vingar do capitão por causa da sua teimosia. Foi culpa dele, essa maldita obstinação que nos meteu nessa enrascada.";
			link.l1 = "Mas como você acabou encontrando aquele pirata em primeiro lugar?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Eu não sei. Era uma patrulha comum, e havia um navio comum navegando sob a bandeira de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Não faço ideia do motivo pelo qual o capitão decidiu inspecionar, mas eles ignoraram o tiro de advertência e, quando nos aproximamos, içaram a bandeira negra. "+"Não tivemos o apoio do forte, então a luta não foi fácil. Depois veio o abordo. Até hoje não sei como conseguimos derrotá-los.\n"+"Bem, e nós vimos toda aquela carga preciosa. O próprio diabo deve ter nos dado aquilo. Tivemos que esconder a carga em terra e explodir o navio capturado pelos ares. Ele estava danificado demais.";
			link.l1 = "Você não tem medo de que todo o seu esforço e sacrifício acabem sendo em vão se os homens do governador descobrirem o esconderijo?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "They won't find it. I blasted the cave's entrance well; after all, I was the best explosives expert in the whole squadron. Only smugglers can find my stash, they know every inch of this place.\n"+"Look, I myself have no clue what to do with the booty. I can't sell it or move it away on my own. Besides, no one will do business with a cracked skull. I don't want to profit from the deaths of my crew mates, but I can tell you the location of the stash for "+pchar.GenQuest.CaptainComission.Sum+"  pesos if you take me to "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Concordo. Aqui está o seu dinheiro. Agora fale.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Droga! Tá bom, espera aqui, eu vou buscar o dinheiro.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "Isso é demais, camarada. Além disso, não tenho um navio adequado. Bem, boa sorte pra você e até mais...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Tá bom, então. Me encontre hoje à noite depois da meia-noite por volta de "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+". E certifique-se de que há espaço no seu porão para "+pchar.GenQuest.CaptainComission.GoodsQty+" pcs. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Seria uma pena jogar qualquer coisa disso fora..."; // belamour gen
			link.l1 = "Deixa comigo. Te vejo na enseada...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "E aqui está você, finalmente. Já estava começando a me preocupar. Achei que fosse me entregar para as autoridades.";
				link.l1 = "Eu ainda não enlouqueci. Aqui está o seu dinheiro. Agora é a sua palavra.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Então, onde está o dinheiro?";	
				link.l1 = "Droga! Tá bom, espera aqui, eu vou buscar.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Capitão, parece que chegamos tarde. Os contrabandistas já encontraram o esconderijo.";
			link.l1 = "Eu não vou entregar meu tesouro, nem mesmo o diabo conseguiria tirá-lo de mim.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Cansei, resolva com seus concorrentes sozinho.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Capitão, temos um assunto sério aqui. Aconselho que leve seu esquadrão embora antes que nossos navios cheguem.";
			link.l1 = "Senhores, parece que estão tentando pegar o que não lhes pertence.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Ah, é mesmo?! Você faz ideia de com quem está falando?";
			link.l1 = "Estou falando com você, amigo. Essa carga tem um dono legítimo, e eu estou aqui em nome dele.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "Não vamos permitir que você se meta nos nossos assuntos, nem que fosse o Messias do nosso Deus! Saia do caminho se valoriza a sua vida!";
			link.l1 = "Eu não fui claro o bastante? Essa carga é minha, e não vou sair daqui sem ela!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "Que nada! Se você quer tanto assim, então vai esperar por isso aqui, pra sempre!";
			link.l1 = "O destino vai decidir quem vai ficar aqui para sempre.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Capitão, mande seus homens se apressarem, uma patrulha pode chegar a qualquer momento. Além disso, os contrabandistas claramente também estavam esperando seus transportes.";
			link.l1 = "É, precisamos nos apressar... Carregue a carga no porão e vamos sair daqui.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Obrigado, capitão "+GetFullName(pchar)+". Se não fosse por você, os contrabandistas teriam levado nossa carga, e aqueles homens que caíram defendendo-a teriam morrido em vão...";
			link.l1 = "E obrigado por confiar em mim.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Tenho um amuleto aqui, devo minha vida a ele. Por favor, aceite, pode ser seu talismã da sorte. E obrigado mais uma vez, amigo. Que os ventos estejam sempre a seu favor.";
			link.l1 = "Obrigado pelo presente, não esperava por isso. E é bom cuidar da sua saúde enquanto ainda tem moedas no bolso.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Aparentemente, hoje é meu dia de receber visitas. Precisa de mim?";
			link.l1 = "Se você é o capitão "+pchar.GenQuest.CaptainComission.Name+", então sim.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...ex-capitão"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "Eu sou "+GetFullName(pchar)+", e tenho algumas perguntas para você.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "E por que você acha que eu responderia a elas?";
			link.l1 = "Capitão "+pchar.GenQuest.CaptainComission.CapName+" pediu para eu te avisar que as circunstâncias envolvendo a destruição de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" ficou conhecido pelas autoridades, "+"mas não vi seu navio na viagem de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "E onde está o capitão "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Ele morreu.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Entendi... Então é assim, hein? Agora muita coisa faz sentido. Então, alguém andou fofocando que a gente saqueou "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+". "+"Mais cedo ou mais tarde, eles vão encontrar a carga e me enforcar. Capitão "+pchar.GenQuest.CaptainComission.CapName+" está morto, isso significa que ninguém pode me ajudar\nSó você\n "+GetFullName(pchar)+", me tira daqui e eu vou te recompensar por isso.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "O governador recebeu uma mensagem do dono da carga. E os números nela são bem impressionantes, sabia?";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "Mas com certeza você não acha que eu vou te ajudar de olhos vendados?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "O governador recebeu uma mensagem do dono da carga. E os números nela são bem impressionantes, sabia?";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "Estão dizendo na colônia que você anda se envolvendo com os contrabandistas...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Parece que vou ter que te contar toda a história.\n"+"Durante uma das minhas patrulhas regulares, encontrei uma embarcação hasteando a bandeira de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Eles ignoraram minhas ordens de se render. "+"Tínhamos chegado "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"Depois de uma breve perseguição, eles içaram a bandeira negra. O forte estava bem longe, então tivemos que lutar sozinhos. Eles destruíram nosso gurupés, por isso não conseguimos evitar o abordo.\n"+"Foi por pouco, mas conseguimos matar todos eles  graças à Santa Maria e a uma unidade de mosqueteiros. Imagine a nossa alegria quando descobrimos que "+sTemp+" estava cheio de objetos de valor. "+"Decidimos que esta é uma recompensa justa pelas nossas feridas e pelas mortes dos nossos homens\nJá estava escuro, mas conseguimos levar "+sTemp+" até a baía mais próxima e escondemos a carga em terra. Depois, queimamos "+sTemp+" e eu denunciei um navio pirata afundado. Claro, não falei nada sobre a carga.";		
			link.l1 = "Acho que não faz sentido você tentar me enganar. Então, proponho um acordo: você me mostra o esconderijo e eu te levo para onde quiser no arquipélago.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ha-ha-ha... Não, capitão, não vou sair do povoado sem a minha parte, nem que eu tenha que ir para a forca.";
			link.l1 = "Certo. Você vai receber a sua metade.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hum... Sabe, não estou disposto a arriscar o pescoço pelo seu bem-estar. Adeus...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Agora sim, estamos falando a mesma língua. Estou pronto\nPrimeiro, você precisa me esconder a bordo do seu navio. Vou te mostrar a baía onde o tesouro está escondido.";
			link.l1 = "Então vamos agir rápido e juntos. Vou abrir sua cela, e você me segue. Não fique para trás e nada de perguntas até sairmos do forte.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Obrigado por me resgatar. Vamos seguir em frente "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+", eu vou te mostrar onde está o esconderijo. É melhor a gente se apressar antes que os selvagens encontrem.";	// belamour gen	
			link.l1 = "Tem certeza de que vamos conseguir levar toda a carga?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Você está certo, certifique-se de ter espaço suficiente para "+pchar.GenQuest.CaptainComission.GoodsQty+" peças de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Seria uma pena perder um saque tão valioso, ainda mais com tanto sangue derramado por ele. Eles não vão nos dar uma segunda chance.";
			link.l1 = "Eu cuido disso.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Capitão, não precisamos de testemunhas. Por favor, tente convencer essas pessoas a sair da enseada.";
			link.l1 = "Certo, vamos fazer isso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Capitão, me desculpe, mas este não é o melhor lugar para seus exercícios. Aquele cais já está ocupado.";
			link.l1 = "Senhores, não vim aqui para passear. Tenho negócios a tratar aqui.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Bom, também não estamos pescando águas-vivas aqui, então virem seus navios e caiam fora daqui.";
			link.l1 = "Não quero perder meu tempo tentando te convencer a sair. Ou você vai embora por bem e vive, ou fica aqui pra sempre.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Vejo que você tem dificuldade em entender o que eu digo. Tudo bem, é problema seu...";
			link.l1 = "Assim está melhor!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Chegamos. O esconderijo está numa fenda daquela rocha. A entrada está bloqueada por pedras. No esconderijo, tem "+pchar.GenQuest.CaptainComission.GoodsQty+" unidades de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Lembre-se que metade disso é minha?";
			link.l1 = "Com certeza. Temos um tempo enquanto meus homens carregam a mercadoria. Vamos conversar sobre para onde você e sua carga precisam ser levados.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Muito bem. Agora me diga, existe algum motivo para eu compartilhar?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Capitão "+pchar.GenQuest.CaptainComission.Name+", tenho que te contar uma coisa desagradável. Eu trabalho para o governador. E pretendo entregar a ele toda  a carga que você escondeu. É melhor você voltar para a prisão e esperar lá pelo seu destino.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Muito bem. Mas é o seguinte... No começo eu queria te entregar para as autoridades, mas por que eu faria isso agora? E por que eu dividiria com você?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Preciso chegar a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", em "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" para "+pchar.GenQuest.CaptainComission.iDay+" dias. Meu pessoal lá já deve ter preparado a carga para venda."; // belamour gen
			link.l1 = "Certo. Então está na hora de partir.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Certo. Sempre se deve confiar na cabeça, não no coração. Vivendo e aprendendo.\nMesmo que eu não esperasse por isso, estou sempre pronto pra uma briga. Você vai pagar pela sua traição.";
			link.l1 = "Bem, se você tiver sorte...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Certo. Sempre se deve confiar na cabeça, não no coração. Vivendo e aprendendo\nMesmo que eu não esperasse por isso, estou sempre pronto para uma briga. Você vai pagar pela sua traição.";
			link.l1 = "Estou ao seu dispor...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Aparentemente, chegamos tarde... Os clientes não esperaram, e eu não tenho como organizar sozinho o armazenamento e a venda da carga...";
			link.l1 = "Você tem alguma proposta específica a esse respeito?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitão "+GetFullName(pchar)+", eu sei que é meio estranho, mas... você poderia me dar o valor em dinheiro da minha parte? Eu acho que, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos pode ser um bom acordo.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Sim, é um preço justo. Não me importo. Aqui está o seu dinheiro, até logo.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Ah, não, meu amigo, assim não dá. Não posso cuidar de você pra sempre. Se não quiser buscar sua carga, eu fico com ela. Pode deixar, vou dar um jeito de guardar e, mais cedo ou mais tarde, vender tudo.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Espere um pouco, capitão. Quero te agradecer por ter me resgatado. Sabe, eu já estava quase perdendo a esperança... Aqui, tenho certeza de que esse amuleto vai te ser bem útil em muitas situações difíceis... Agora, adeus.";
			link.l1 = "Valeu. Não esperava por isso. Foi um prazer fazer negócio com você.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Eu não esperava isso de você... Pelo visto, não tenho outra opção a não ser te desafiar para um duelo.";
			link.l1 = "Estou ao seu dispor...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Capitão, preciso falar com meus homens.";
			link.l1 = "Pode ir em frente.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Saúdo você, Capitão "+GetFullName(pchar)+". Então, trouxe toda a carga? E onde está o capitão "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" morreu, e eu fui preso por uma denúncia. E se o capitão "+pchar.CaptainComission.FullName+" se não tivesse me ajudado, você não teria me visto nem a carga.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "E também "+NPCharSexPhrase(sld,"Quem é ele? Ele é","Quem é ela? Ela é")+" ciente dos nossos assuntos?";
			link.l1 = "Claro. "+NPCharSexPhrase(sld,"Ele tirou","Ela tirou")+" me from the jail and undertook to deliver half of the cargo here; the other half I promised "+ NPCharSexPhrase(sld, "him","her") +" as a compensation.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Ah, capitão, de jeito nenhum. Isso é problema seu! Eu sugeri que a gente pegasse o navio e fosse embora, mas você se importou demais com essa sua maldita carreira. E olha só, agora seu querido governador te jogou na prisão."+" Sua parte foi muito menor que a metade! A gente não arriscou o pescoço sob a chuva de balas só pra você ficar com metade pra si!";
			link.l1 = "Escuta, contramestre, você não se lembra que o navio ficou totalmente destruído? Que ele quase afundou? Não entende que, se eu não tivesse dado metade para esse homem, você nunca mais veria nem um pedacinho da carga?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Você não vai me enganar! Como podemos saber que você não estava de conluio? E se nem houve prisão nenhuma? E se você só ficou ganancioso demais e resolveu roubar nossas coisas? Ou acha que esquecemos como se usa uma lâmina?!";
			link.l1 = "Vejo que você enlouqueceu. Só consegue ouvir o tilintar das moedas nos seus ouvidos.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Rapazes! Olhem só como nosso capitão está falando agora! É, a ganância tomou conta dele de vez! Ele vendeu nossa parte para "+NPCharSexPhrase(sld,"um canalha","uma aventureira")+"!!";
			link.l1 = "Cale essa boca imunda agora, ou eu calo você pra sempre!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Me desculpe, capitão, por você ter que presenciar essa cena ridícula e ainda por cima participar dela. É difícil acreditar que há apenas um mês éramos uma tripulação unida, e cada um de nós teria dado a vida de bom grado para salvar um amigo.";
			link.l1 = "Tenho que admitir, não consigo imaginar isso, sem querer ofender.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Infelizmente, não tenho como organizar sozinho o armazenamento e a venda da carga...";
			link.l1 = "Você tem alguma proposta específica a esse respeito?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitão "+GetFullName(pchar)+", eu sei que é meio estranho, mas... você poderia me dar o valor em dinheiro da minha parte? Acho que, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos pode ser um bom acordo.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "Certo, não me importo. Aqui está seu dinheiro, e adeus.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "Não, isso não vai funcionar. Você pode pegar sua carga ou deixá-la no porão, mas não vou te dar uma única moeda.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Espere um pouco, capitão. Quero te agradecer por ter me resgatado. Sabe, eu já estava quase perdendo a esperança... Aqui, tenho certeza de que esse amuleto vai te ser muito útil em várias situações difíceis... Agora, vou indo. ";
				link.l1 = "Obrigado. Não esperava por isso. Foi um prazer fazer negócios com você.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Espera... Acabei de pensar... Sabe, minha carreira acabou, estou sem tripulação e sou um exilado na minha própria terra. Com certeza você precisa de homens de confiança, com mão firme e que sabem guardar segredo. Por favor, me aceite na sua tripulação, prometo que você não vai se arrepender.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Pra ser sincero, já faz um tempo que espero você aceitar. Claro. Me encontre a bordo.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hum... sabe, me parece que você é esperto demais pra servir a alguém. Adeus...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Bom, pelo visto, hoje definitivamente não é o meu dia de sorte... Tudo bem, capitão, vamos sacar as lâminas e acabar logo com isso de uma vez...";
			link.l1 = "Estou ao seu dispor...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Isso não te diz respeito. Agora me diga, o que você está farejando por aqui? Não está procurando por um homem que acabou de ser detido?!";
				link.l1 = "Um homem?! Não...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Que bom pra você. Caso contrário, ia acabar na cadeia também, junto com ele. Então não se mete aqui, marujo. Cai fora!";
				link.l1 = "É, é melhor eu ir...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Ótimo! Devíamos ir até a taverna procurar aquele contrabandista agora. Não quero ficar aqui parado!";
				link.l1 = "Sem problema com isso. Vamos lá...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "He-he... Parece que "+GetSexPhrase("companheiro","moça")+", logo você vai fazer companhia pra ele no inferno... Ei, camarada - vamos acabar com os dois!";
				link.l1 = "Seu porco imundo! Defenda-se!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Obrigado mais uma vez, "+PChar.name+". Adeus...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Uma recompensa?! Ah, claro. Aqui – pegue "+FindRussianMoneyString(iMoney)+" e adeus...";
				link.l1 = "Adeus...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Heh! Você acha que a gente vai engolir essa conversa fiada?! Rapazes, peguem esses dois condenados à forca!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Oficial, você está cometendo um grande erro ao tentar prender duas pessoas inocentes. Acredite, eu não conheço esse homem e não poderia me importar menos com ele."+" Tenho certeza de que seu comandante ficará bem descontente com você se detiver dois cidadãos cumpridores da lei... ";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hum... Sim, talvez você tenha razão. O comandante com certeza não vai gostar disso. Sabe de uma coisa - vamos simplesmente esquecer esse pequeno incidente.";
				link.l1 = "Thank you, officer, you've saved us time. I'd like to ask you to be more careful next time; surely you wouldn't want to be demoted, would you?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "Não, de jeito nenhum. Nesse caso, por favor, dispersem-se. Até mais...";
				link.l1 = "Assim está melhor!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Excelente! E agora pode dar o fora!";
					link.l1 = "O quê?! E o dinheiro? A gente tinha um acordo...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Valeu pela entrega. Agora pode dar o fora... espera, alguém está vindo...";
						link.l1 = "O quê?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Ótimo. Obrigado pela entrega. Aqui, pegue "+FindRussianMoneyString(iMoney)". E lembre-se de que os contrabandistas nunca esquecem gente boa...";
					link.l1 = "Eu espero que sim. Adeus.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Escuta... você e eu nunca fizemos nenhum acordo. Vai cobrar seu dinheiro de quem fez esse trato com você.";
				link.l1 = "Bom, hoje definitivamente não é o meu dia de sorte, o que mais posso dizer?! Tá certo, até mais...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"Você vai pagar por isso! Prepare-se para morrer!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Você teve a ousadia de me desafiar, "+GetSexPhrase("pirralho","lixo")+"?   Bom, você com certeza não faz ideia do que é bom pra você.   Eu vou te abrir!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Meio mil de homens! E o baú do morto! Hic!","Beba! Hic! E o diabo já levou o resto - Hic! -");
						link.l1 = "Oh... Bem. Olá, senhor "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Certo, vamos ver agora... Três pedaços de lona de vela, tábuas para o casco do navio, trocar as cintas e as cordas dos estais...";
							link.l1 = "Olá, senhor "+GetFullName(NPChar)+". Eu sou o capitão "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Saia do meu navio agora, tenho muito o que fazer sem você!","Você já recebeu seus livros, o que mais você quer?!","Eu fiz tudo o que você pediu, o que mais você quer de mim?!");
							link.l1 = "Não se empolgue tanto senão vai acabar tendo um ataque do coração!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rum, rum! Me dá rum... Hic!","Faz tempo... hic... que eu não ficava bêbado assim...");
					link.l1 = "É, seu porão está cheio... talvez seja hora de procurar uma enseada?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Por favor, sente-se, capi-hic-tão! O que vai beber?","Sente-se, capitão! O que vai querer beber? Hic...");
					link.l1 = "Obrigado, mas eu prefiro uma conversa agradável com um homem decente.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Você está tentando... hic! ...me insultar?.. Não tem um homem decente naquela taverna! Hic! Só tem bandido e assassino! Todos uns chantagistas, e aquele lá... o pior de todos! O chefe deles, com uma moreia entalada na garganta!";
				link.l1 = "Estou falando de você. É com você que quero conversar. E quem é o chefe dos bandidos, e por que ele...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Mis"+GetSexPhrase("ter","s")+"! Minha querida! Qual era mesmo o seu nome? Eu te respeito! Ninguém até agora chamou um velho lobo do mar de homem decente! Eu faria qualquer coisa por você! Te daria todo o meu dinheiro, até o último peso!.. Ah, esqueci. Estou sem dinheiro. Nem um realzinho me sobrou. Aquele desgraçado, aquele agiota levou até a última moeda, que os demônios usem as tripas dele como pólvora no inferno!";
				link.l1 = "Senhor capitão? Está bem? Percebe que está delirando? Que pergaminhos?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Não, não! Este velho capitão pode estar bêbado, mas ainda mantém o juízo. Os livros e os pergaminhos foram dados a mim pelo Padre "+PChar.GenQuest.ChurchQuest_1.ToName+", eu estava levando eles para "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+". E de manhã fui à igreja local e mencionei esses livros para o padre daqui. Claro, ele quis ver — você sabe como eles são, ficam fascinados com as vidas dos santos e tudo mais. Então mandei um grumete buscar o baú com eles. E enquanto esperava, resolvi apostar um pouco... e de algum jeito perdi todo o meu dinheiro. Tudo! Não sobrou nada pra pagar a bebida! Aí o dono da taverna pegou os livros como garantia, e acabei entregando também os pergaminhos...";
				link.l1 = "Então, você vendeu livros, os livros sagrados que o padre confiou a você  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Eu sei, eu sei... Vou queimar no Inferno por toda a eternidade. Agora não posso nem mostrar a cara para o padre que me deu aquela tarefa, nem para quem estava entregando os papéis, nem para o pessoal daqui... Quem vai rezar pela minha alma agora? E se me excomungarem? Ai, pobre de mim... Preciso de uma bebida... ";
				link.l1 = "Calma, não é tão ruim assim. Suas ações foram péssimas e ímpias, mas mesmo assim estou disposto a te ajudar. Vou pagar sua dívida e comprar esses manuscritos. Além disso, como já conheço os dois padres mencionados, vou navegar direto para  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" para entregar os papéis lá. Fechado?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Salvador! Anjo de Deus... Claro, eu aceito! Eu te daria tudo... tudo mesmo! Se ao menos eu pudesse tomar mais um gole...";
				link.l1 = "Acho que você já teve o suficiente... Ah, tanto faz. Vou comprar mais rum pra você com o balconista.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...e os lençóis! Precisamos trocar os lençóis também!.. Ah, oi. Por favor, não se ofenda, moça"+GetSexPhrase("ter","s")+" seja-lá-qual-for-seu-nome, mas agora, como pode ver, estou bastante ocupado, então se tem algum assunto comigo, seja breve, por favor.";
				link.l1 = "Pelo que eu sei, Padre "+PChar.GenQuest.ChurchQuest_1.ToName+" te dei uns papéis sagrados em "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+". Você prometeu entregá-los para "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" porque você já estava navegando naquela direção mesmo."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Eu estava indo naquela direção, até que aquela tempestade maldita quase destruiu meu velho barco, e acabei preso aqui sabe-se lá por quanto tempo! Esses trapaceiros do cais ficam tentando me empurrar tábuas podres que a maré trouxe pra terra, pra consertar o casco, e pras velas, uns panos velhos que as avós deles usavam pra dormir quando ainda eram jovens.";
				link.l1 = "Senhor, da próxima vez ouvirei com prazer suas histórias magníficas, mas agora gostaria de saber mais sobre o destino dos livros e manuscritos que o senhor recebeu em "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Dat")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Ninguém, está ouvindo? Ninguém ousa me culpar pelo atraso na entrega desses malditos papéis!";
				link.l1 = "Ah, não, de jeito nenhum quis dizer isso. Só queria aliviar seu fardo. É que "+PChar.GenQuest.ChurchQuest_1.ToName+" está bastante preocupado com os livros e papéis que precisam ser entregues a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+". Na verdade, estou indo navegar para lá agora mesmo.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Me parece, senhorita"+GetSexPhrase("ter","s")+", que você tem um conselheiro espiritual em cada porto. Embora isso não seja da minha conta. Se você se importa com essas bobagens, então pegue seus livros e suma daqui! Já vai tarde!";
				link.l1 = "Obrigado, Capitão. Boa sorte com os seus reparos.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Não se preocupe com isso, moça"+GetSexPhrase("ter","s")+", e viajar para "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" com leveza, já que fui eu quem se comprometeu a entregar esses papéis, e serei eu quem fará isso a qualquer custo, para que ninguém saia gritando por aí que o capitão "+NPChar.name+" não cumpriu com a palavra dele!";
				link.l1 = "Mas, Capitão, a questão na verdade é...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Na verdade, a questão é que eu não tenho nada a tratar com você. O Santo Padre me deu uma missão, entregar os livros para "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" e entregue-os ao padre local. E não vejo você lá. Nem um pouco! Boa sorte.";
//				link.l1 = "Certo, então. Você é um homem muito responsável, embora esse seja seu único mérito. Boa sorte pra você, meu amigo descortês";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "Já tive o bastante do seu comportamento insolente. Sua boca tola seria capaz de tirar até um anjo do sério. Preciso cumprir a vontade do meu santo pai, e vou usar minha arma se for preciso!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Calma, calma, Capitão "+PChar.name+"! O que há de errado com você? Ah, tudo bem, vejo que se não trouxer esses papéis, todos aqueles Santos Padres vão ficar bem irritados com você, sem falar no nosso Pai do Céu. Certo, pegue seus tesouros teológicos e vá com a bênção de Deus.";
				link.l1 = "Fico feliz que você não só entendeu minha posição, mas também lembrou do meu nome. Sugiro que se lembre dele toda vez que estiver prestes a fazer alguma besteira.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Cai fora...","Não me incomode!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"Você não devia ter dito isso! Agora vou ter que te mandar pro Senhor pra rezar pelo perdão dos meus pecados!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"Você não devia ter dito isso! Agora vou ter que te mandar pro Senhor pra rezar pelo perdão dos nossos pecados!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"Você não devia ter dito isso! Agora vou ter que te mandar pro Senhor pra rezar pelo perdão de todos os nossos pecados!";
			}
			
				link.l1 = "De jeito nenhum, camarada. Cada um vai prestar contas a Deus por si mesmo!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Ei, por que essa grosseria? E se eu tiver negócios com você.";
				link.l1 = "Isso sim é novidade! Olha, não tenho tempo pra conversa fiada com gente como você!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Bem, também não vou ficar de papo longo com você. Mas talvez se interesse em comprar umas bugigangas por um bom preço?";
				link.l1 = "Eu pareço algum maldito receptador?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Calma, calma, não tem ladrão aqui entre nós! Esse vaso foi dado pra gente pelo nosso trabalho honesto! Olha só... ouro puro, enfeitado com pérolas. Mas a questão é que não serve pra nada pra nós. Então só queremos vender e dividir o dinheiro.";
					link.l1 = "Deixe-me dar uma olhada mais de perto... Meu Deus! Este é o cálice da comunhão!!! Então, vocês são os blasfemos que saquearam a igreja de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Aí está você!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Quieta, moça"+GetSexPhrase("ter","s")+" Hipócrita! Sabe, estamos meio apertados de grana, então resolvemos vender umas coisas. Dá uma olhada nesse vaso... ouro puro, enfeitado com pérolas. Preço especial pra você, digamos, mil moedas.";
				link.l1 = "Deixe-me dar uma olhada mais de perto... Meu Deus! Este é o cálice da comunhão!!! Então, vocês são os blasfemadores que saquearam a igreja de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Aí está você!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Calma aí, moça"+GetSexPhrase("ter","s")+"!.. Droga, eu disse pra aquele cabeça-oca não fazer escândalo antes da hora certa...";
				link.l1 = "O que você está tagarelando? Muito bem, escolha: ou me entrega o butim roubado de boa vontade, ou eu chamo os guardas.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Escuta, "+GetSexPhrase("bom homem","moça")+", não precisamos de confusão, então vamos resolver isso de forma pacífica. Você tem que acreditar em nós, nós realmente não saqueamos aquela igreja, nem temos dinheiro algum. É verdade, recebemos alguns pesos e aquele enfeite dourado só por fingir que cometemos o roubo. E este cálice dourado foi a única coisa que sobrou depois que pagamos os contrabandistas...";
				link.l1 = "Então, você está tentando dizer que...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "Aquele maldito padre nos contratou, é isso que estou dizendo! Mas por que ele tinha que mandar você atrás da gente?.. Bem, agora estamos quites. Pegue este vaso e mostre para aquele hipócrita, você vai ver como ele vai se contorcer feito lula na areia!";
				link.l1 = "Me dá a caneca e cai fora, antes que eu mude de ideia.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Você fala bonito, mas não sou tão fácil de enganar. Se quiser me convencer, convença a minha lâmina primeiro.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"Eu não falei praqueles desgraçados: mantenham as mãos longe e peguem só o dinheiro do padre!";
			}
			else
			{
				dialog.text = RandSwear()+"Eu não disse praqueles desgraçados insaciáveis: mantenham essas mãos gananciosas longe de tudo e só peguem o dinheiro do padre!";
			}
			
					link.l1 = "O que você está resmungando? Muito bem, escolha: ou me entrega o que roubou de boa vontade, ou eu chamo os guardas.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Estou fazendo uma escolha diferente, então cale essa boca e entregue sua bolsa, e eu poupo sua vida.";
				link.l1 = "Vou te ajudar a conseguir uma audiência com nosso Senhor agora!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Certo, vou te dar um dinheiro, mas só porque eu quero, pra que você e seus amigos possam levar uma vida honesta e não precisem se rebaixar a roubar.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... Tudo bem, vamos deixar nossas diferenças de lado e voltar ao começo da nossa conversa. Então, quanto você queria por aquela coisa?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Também não quero confusão, "+GetAddress_Form(pchar)+", mas agora o preço aumentou. Por essa taça preciosa, vou exigir tudo o que você tem com você.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Seu verme ganancioso! Eu só tenho "+FindRussianMoneyString(iMoney)+" comigo. Pegue isso e suma daqui!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Escolha errada, rato ganancioso. Você não vai se dar bem às minhas custas!"+GetSexPhrase(" I am as free as the wind - here today, gone tomorrow; today I am poor - tomorrow I shall be rich...","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Você não está querendo dizer que, especialmente hoje "+GetSexPhrase("você é pobre","você não tem dinheiro")+"?!";
				link.l1 = "Exatamente, meu amigo ganancioso, para sua grande decepção. Agora preciso me retirar, tenho muito o que fazer.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Pare! Nós vamos verificar isso, e se você não tiver falado a verdade, vou enfiar sua língua mentirosa num formigueiro!";
				link.l1 = "Depois de dizer isso, você está acabado!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Ah, não tem nada pra decidir. A gente resolve tudo por conta própria. Mas vamos pegar seu navio e cair fora daqui.";
			link.l1 = "Tem uma condição: primeiro, você vai ter que tirar minha lâmina de mim...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Olá, capitão! Parece que a própria Providência te enviou para salvar "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" e os homens dele. Estamos precisando muito de ajuda aqui."+"Nosso "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" naufragou na tempestade nos recifes daqui, e as ondas arrastaram a tripulação sobrevivente para a praia."+"Por "+(5+hrand(7))+"Por semanas ficamos olhando para o horizonte, esperando ver a vela de um navio que viesse nos resgatar.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("É, esse é um destino nada invejável. Mas essa é a vida de marinheiro, qualquer um pode acabar no seu lugar.","Entendo... Deus segura todas as vidas, só que Ele está ocupado demais pra lembrar de todo mundo."),RandPhraseSimple("De fato. O homem propõe, mas Deus dispõe.","É, isso aí foi mesmo um baita azar."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "Foi muito sério! Aquele canalha "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" não consegui pensar em outro castigo além de ir embora "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" numa ilha deserta, feito um cão sarnento! "+"Ele esperava que o sol e a sede nos ressecassem como um peixe seco no varal de um pescador! Mas ele estava enganado, pois a própria Providência ficou do nosso lado, mandando você aqui para nos salvar...";
				link.l1 = RandPhraseSimple("Calma aí, amigo. Pelo que vejo, vocês são homens de profissão livre, e não vieram parar aqui por acaso.","Já falando sobre salvação? Pelo que entendi, você está aqui por causa de algumas conquistas especiais.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Capitão, por favor, seja uma alma bondosa e ajude  "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" homens desamparados. Você é nossa única esperança, exceto por nosso bondoso Senhor.","Capitão, você tem algum armário livre no seu navio para "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" homens arruinados?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Oh... e para onde você quer que eu te leve?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("I am truly sorry, but there isn't a single free hammock, let alone a cabin. The sailors are sleeping on deck; they can't even get a proper night's rest after their watch...","I would really hate to disappoint you, but the ship is overloaded, and people have to sleep in bad weather. Should there be an outbreak of disease, I will lose half the crew."),RandPhraseSimple("I am truly sorry, but there is absolutely no spare crew space on my ship. I cannot take on any more passengers.","I have to disappoint you, but my ship is overloaded with crewmen. I fear the epidemic..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Você é um marinheiro experiente e devia saber que a presença de alguém que sobreviveu a um naufrágio é um péssimo presságio. Meus marinheiros vão simplesmente jogar todos vocês ao mar.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Hmm... Sabe, por vários motivos gostaríamos de ficar o mais longe possível das autoridades... Por favor, desembarque a gente em alguma enseada de uma ilha habitada ou no continente, e aí conseguiremos nos virar.";
			link.l1 = "Bem, tenho beliches e redes de sobra. Suba no barco.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... má sorte... Temos batalhas pela frente, e não sei onde você estará mais seguro, a bordo do meu navio ou nesse refúgio aconchegante.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "Oh, capitão! São tempos em que a gente não se sente seguro nem na cama com a esposa, imagina então no mar... Olha esses brutamontes, cada um deles tá pronto pra enfrentar canhões com as próprias mãos. Segurança ou conforto não é com eles, dá pra ver na cara de cada um!";
			link.l1 = "Nos rostos deles, só consigo ver a vontade de apunhalar pelas costas o seu tolo benfeitor.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... Na verdade, essa é uma boa ideia. Me diga, amigo, seus capangas estariam dispostos a servir na minha tripulação?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Que pena, capitão... Vejo que não vamos resolver isso de maneira amigável. Acho que vou ter que te lembrar do código do mar. E lembre-se: quando se trata de abordagens, ninguém faz melhor que a gente...";
			link.l1 = "Bem, agora finalmente posso ver quem você realmente é...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Mas é claro! Eles ficariam felizes em fazer parte do seu grupo de abordagem! Ninguém vai superá-los numa briga, só talvez o próprio Davy Jones! Ha-ha-ha!";
			link.l1 = "Tá bom, então. Entrem nos barcos...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Obrigado, capitão! O carregamento não deve demorar muito. Deus, como rezamos para que esse momento chegasse!";
			link.l1 = "Muito bem, então.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Por que está demorando, capitão? Dê a ordem para içar âncora.","Desculpe, capitão, mas precisamos nos preparar para zarpar.","Que sorte a nossa você ter decidido vir aqui!");
			link.l1 = "Anda logo. O navio não vai esperar por ninguém.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Thank you, captain. Indeed, we were right to believe in our luck... Please, accept this gem; I found it at that ill-fated cove. I hope it brings you luck.";
				link.l1 = "Eu não esperava um presente desses.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Capitão, por favor, não pense que estamos sendo atrevidos, mas estamos mesmo sem dinheiro. Sabe, perdemos tudo o que tínhamos. Poderia nos emprestar uns trocados? Prometemos que vamos te pagar de volta... assim que surgir uma oportunidade...";
				link.l1 = "Mas que ousadia! De fato, a insolência não tem limites. Bem, a única coisa que posso fazer por você agora, depois de tudo que já fiz, é não contar às autoridades sobre você.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "É mesmo... E quanto você quer?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Obrigado, capitão.","Capitão, somos muito gratos a você.","Vamos rezar por você, Capitão "+PChar.name+"!");
			link.l1 = "Boa sorte pra você. Adeus...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, capitão... Sabe, a gente se deu bem... Seria mesmo uma pena ter que te matar...";
			link.l1 = "Pode tentar!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Bem, diga, "+iMoney+" pesos para cada um de nós cairiam muito bem... Claro, se você não achar que essa compensação por toda nossa dor e sofrimento é pouca coisa, he-he...";
			link.l1 = RandPhraseSimple("Pelo contrário, tenho certeza de que isso é demais... Uma corda no pescoço de cada um de vocês seria o melhor.","Eu mesmo te penduro nas palmeiras como macaco por esse dinheiro!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Certo, pegue. Espero mesmo não te dever mais nada, hein?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Que generosidade! Sinceramente, achei que você já tivesse percebido que a gente sempre consegue o que quer. E desta vez, também não vamos recuar...";
			link.l1 = "Pode tentar!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Ah não, capitão, o que você está dizendo?! Com certeza vamos acender uma vela no seu nome, se algum dia a gente pisar numa igreja... hah!";
			link.l1 = "Espero que sim...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Ah não, capitão, o que está dizendo?! Com certeza vamos acender uma vela em seu nome, se algum dia a gente pisar numa igreja... hah!";
				link.l1 = "Espero que sim...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Heh, capitão, sabe, isso não é bem um problema. Eu e meus rapazes estamos dispostos a liberar uma dúzia de redes no seu navio tirando quem está ocupando elas agora...";
				link.l1 = "Hmm... isso parece uma ameaça...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Bem, na verdade, isso é uma ameaça. Eu preciso do seu navio, e vou sair deste lugar, com ou sem o seu consentimento!";
			link.l1 = "Bem, agora eu posso finalmente ver quem você realmente é...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Eu entendo você, capitão. Entendo perfeitamente... Quem iria querer cuidar de piratas miseráveis que só imploram pela forca?.. Mas... e se eu te fizer uma proposta? Você nos leva até alguma enseada em uma ilha habitada ou no continente, e eu te dou um mapa do tesouro em troca. Temos um acordo?";
			link.l1 = "Hmm... E como você pode garantir que esse mapa não é uma falsificação?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ha, tenho certeza de que seu mapa vale tanto quanto o pedaço de papel em que foi desenhado...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Bem... Você não nos deixa escolha... Ainda assim, vamos sair deste lugar, com ou sem o seu consentimento!";
			link.l1 = "Bem, agora eu posso finalmente ver quem você realmente é...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "E como você pode garantir que não vai nos entregar para as autoridades no próximo porto? Nós dois estamos jogando sem ver as cartas um do outro...";
			link.l1 = "Certo, temos um acordo.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Obrigado, capitão "+PChar.name+". Você cumpriu"+GetSexPhrase("","")+" sua promessa, chegou a hora "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" para cumprir o meu. Não estou com o mapa agora, mas vou te contar onde está o tesouro. Vá até a enseada...";
			link.l1 = "Ah, então é assim que você fala agora! Já vi que estava planejando me enganar desde o começo...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "Eu sabia desde o começo que não dava pra confiar em você...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "É isso que acontece quando você confia em um pirata. Que tipo de gente vocês são? Nada é sagrado pra vocês!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Não faça escândalo... Não sou santo, mas cumpro minha palavra!";
			link.l1 = "E você espera que eu acredite em você de novo? Pra amanhã o arquipélago inteiro rir da minha cara?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Hum... Pelo visto, não vai ter solução pacífica. Mas, Deus sabe, eu não queria isso...";
			link.l1 = "Desembainhe sua lâmina, ou eu vou te esmagar como o rato que você é!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "E o que mais eu poderia ter feito? Ficar naquele buraco fedorento com meus rapazes e apodrecer até a morte? É melhor você me ouvir..."+XI_ConvertString(sTitle+"Gen")+" capitão "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" tem um esconderijo onde ele guarda o saque. Mas tome cuidado"+GetSexPhrase("","")+", ele costuma ir lá com frequência. Encontrar o esconderijo não será difícil, se você ficar atento..."; // belamour gen
			link.l1 = "E você espera que eu acredite em você de novo? Pra amanhã o arquipélago inteiro rir da minha cara?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Tá bom. Mas se você me fizer de bobo de novo, eu vou te encontrar.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Escute "+sTemp+", ele está falando coisa com coisa.","Não fique bravo com "+sTemp+", ele simplesmente não tinha outra escolha.","Obrigado, capitão.");
			link.l1 = "Boa sorte pra você...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "E o que mais eu poderia ter feito? Ficar naquele buraco fedorento com meus rapazes e apodrecer até a morte? É melhor você me ouvir..."+XI_ConvertString(sTitle+"Gen")+" capitão "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" tem um esconderijo onde ele guarda o saque dele. Mas cuidado, ele passa lá com frequência. Encontrar o esconderijo não vai ser difícil, se você ficar esperto..."; // belamour gen
			link.l1 = "E você espera que eu acredite em você de novo? Pra amanhã o arquipélago inteiro rir da minha cara?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Quem é você?"+GetSexPhrase(" camarada"," garota")+"? E o que te trouxe a este lugar desolado?";
			link.l1 = "Eu parei para reabastecer meu estoque de água fresca.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "Estou aqui em nome de "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Você escolheu um lugar ruim pra isso... Tudo bem, faça no seu tempo.";
			link.l1 = "A-ha...";
			link.l1.go = "exit";
			link.l2 = "E quem é você pra me dizer o que eu devo fazer?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Eu digo a todos o que fazer. E quem se acha esperto demais vai acabar pendurado no coqueiro.";
			link.l1 = "Vou arrancar sua língua, vira-lata.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "E por que ele mesmo não veio?";
			link.l1 = "Ele não quis, ficou em "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" e esperando por mim."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "Aquele velho canalha! Ele está tentando enganar a gente de novo, não está? Assim não dá. Diz pra ele que só vai receber o dinheiro se a gente estiver junto!";
			link.l1 = "Ele me disse para não voltar sem dinheiro e para não levar ninguém a bordo...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Bem, se você confia tanto nele, pode ficar aqui. Mas nós vamos levar seu navio, seu dinheiro e partir para "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+". Estamos loucos para ver a cara de "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "Se sente tanta falta dele, pode nadar até lá... ou morrer aqui.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Você é uma pessoa astuta. Mas permita-me garantir que nosso conflito com o Capitão "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" é puramente ideológico. Eu avisei que as trapaças dele iam ser punidas um dia, e agora meu  "+iBanditsCount+" meus companheiros estão sofrendo por causa do nosso amor por Deus e pela justiça.";
			link.l1 = "Como assim... Aposto que vocês foram os verdadeiros instigadores do motim, e tiveram o que mereciam.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Claro... Ainda assim, seria bom ouvir a opinião do capitão "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" ele mesmo sobre seus desentendimentos.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Capitão, por que ofender pessoas honestas com sua desconfiança? Olhe só para o rosto deles... você realmente acha que são amotinados? São tão humildes quanto um homem pode ser... Mas não ficam atrás de ninguém numa luta por uma causa justa sob um bom comando! Posso garantir pessoalmente por cada um deles.";
			link.l1 = "Certo, mas o que eu faço com você agora?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "O que você quiser. Você decide, nos leve até um povoado ou aceite a gente na sua tripulação, pra mim você parece um bom capitão.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Certo, vou te aceitar na minha tripulação. Mas nada de brincadeiras! Aqui mando com mão firme!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Eu não vou te levar a lugar nenhum. Já tenho bandidos demais na minha tripulação.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Certo, entra no barco, eu vou te levar a um lugar.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Eu juro, capitão, você não vai se arrepender.","Você fez a escolha certa, capitão.","Capitão, pode ter certeza de que você teve tanta sorte quanto nós!");
			link.l1 = RandPhraseSimple("Espero que sim.","Anda logo. O navio não vai esperar por ninguém.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "Isso pode ser facilmente resolvido. Ele navega em  "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" '"+sTitle+" e está envolvido no tráfico de escravos... Vamos fazer assim: Se encontrarmos ele, você fica com a carga e nós ficamos com o navio. Ah, e você também pode perguntar se ele sabe sobre "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+". Espero que ele não se borre todo quando ouvir esse nome, porque é o meu navio..."; // belamour gen
			link.l1 = "Certo, temos um acordo.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "O que diabos você quer de mim?";
			link.l1 = "Vim cumprimentar em nome de "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+". Imagino que você conhece ele?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "É uma pena que eu não tenha estrangulado aquele canalha antes. Bem, acho que chegou a hora de pagar pela minha generosidade...";
			link.l1 = "De fato... E o tempo acabou de se esgotar...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Ótimo trabalho, capitão! Então ficou tudo como combinamos? Nós ficamos com o navio e você com a carga?";
			link.l1 = "Claro. Pegue o navio e faça bom uso dele.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Saúdo você, Capitão "+PChar.name+".";
			link.l1 = "E então, o que acha do seu navio?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh... está rangendo e gemendo, igualzinho a mim. Acho que nenhum de nós dois tem muito tempo sobrando pra navegar por aí...";
			link.l1 = "Boa sorte, então...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Por que você afundou meu navio?! Você ao menos lembra do nosso acordo?";
			link.l1 = "O quê? Eu não queria que ele me afundasse no lugar. Não está vendo que eu mal escapei?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "Quem luta desse jeito? Você perdeu um navio desses! Mas que diabos! O que uma criança como você está fazendo aqui?";
				link.l1 = "Vou arrancar sua língua, vira-lata.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Quem luta desse jeito? Você perdeu um navio desses! Tem ideia de quanto isso me custou? "+FindRussianMoneyString(iMoney)+"! Agora você me deve...";
				link.l1 = "Não seria pedir demais pra você? Não esqueça que eu já te fiz um favor.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Maldito seja você e esse navio maldito! Pegue seu dinheiro e não quero ver você de novo!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "E de que me serve esse favor agora?! Se o capitão "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+" está no fundo do mar agora com meu navio! Agora não recebo nem minha parte, nem meu navio de volta! Que destino, morrer na sarjeta, como um vagabundo!!!";
			link.l1 = "Mas por quê? Posso providenciar um funeral espetacular pra você. Bem aqui, se não se importar...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Eu pensei que talvez pudéssemos... chegar a um acordo, quem sabe? Se você fizer um favor pra gente, a gente retribui, he-he.";
			link.l1 = "Um favor? E qual é o esquema, o que você oferece em troca?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Nosso capitão "+PChar.GenQuest.JusticeOnSale.SmugglerName+" fui pego pela patrulha local de  "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+". Eles o mantêm preso, mas não têm provas suficientes para enforcá-lo. Não podemos tirá-lo de lá sozinhos\n"+"Você é um homem respeitado. Todos te conhecem. Talvez você consiga negociar, pagar a fiança dele, ou simplesmente comprá-lo de volta? Confie em nós, vamos deixar a ilha assim que tivermos nosso homem, então sua reputação não será afetada!"; // belamour gen
			link.l1 = "Digamos que eu possa te ajudar. Mas e o meu pagamento?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Vá para o inferno, criatura do diabo! Não quero nada com você!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Quer alguns amuletos e bugigangas indígenas? São bem raros... Ou prefere dinheiro na hora? Alguns milhares de pesos, que tal?";
			link.l1 = "Vá para o inferno, criatura do diabo! Não quero ter nada a ver com você!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Me interesso por bugigangas indígenas. Acho que vou concordar.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "Dinheiro é o melhor amigo de um marinheiro. Grana não tem cheiro, como todos sabemos. Concordo.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Obrigado, capitão. Vamos te reembolsar pelo valor da fiança além da sua recompensa. Acho que você deveria falar com o comandante sobre o nosso capitão. Talvez consiga convencê-lo. Assim que conseguir tirá-lo de lá, venha até "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", é ali que nosso navio lançou âncora - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+"'. Estaremos esperando por você na praia."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Obrigado, capitão. Vamos te reembolsar pelo valor da fiança além da sua recompensa. Acho que você deveria falar com o comandante sobre o nosso capitão. Talvez consiga convencê-lo. Assim que conseguir tirá-lo de lá, venha até "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", é ali que nosso navio lançou âncora - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+". Estaremos esperando por você na praia."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Chegamos, capitão! Você mandou muito bem enganando aqueles burocratas barrigudos! Aqui está sua recompensa. Rapazes, tragam as bugigangas!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Chegamos, capitão! Você mandou muito bem enganando aqueles burocratas barrigudos! Aqui está sua recompensa. Rapazes, tragam o baú!";
				}
				
				link.l1 = "Me dá a minha parte e cai fora!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Chegamos, capitão! Vejo que você arrumou tudo direitinho. Mas veja bem... não precisamos de testemunhas, então... Vamos agradecer ao capitão, rapazes!";
				link.l1 = RandSwear()+"Eu devia ter atirado em você assim que te conheci!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("Quem é você? E por que está invadindo meu quarto?","Mas que surpresa. Quem é você? Este é o meu quarto, claro, mas não me incomodo com uma companhia dessas. Veio me trazer um pouco de amor?")+"";
			link.l1 = ""+GetSexPhrase("Não é mais seu. O dono da estalagem alugou o quarto pra mim, e já que você não está pagando, está na hora de sair daqui. Agora, podemos fazer isso do jeito fácil ou do jeito difícil. A escolha é sua.","Você está sonhando. No nosso caso, é limpando. Então limpe-se daqui. Agora este quarto é meu, já que, ao contrário de você, eu sempre pago os donos da estalagem.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("Acho que já ouvi falar de você. Tá bom, você venceu, eu vou embora, ainda quero viver...","Hum, já ouvi falar muito de você. Imagino que não seja só sua língua que é afiada. Tudo bem, não fique bravo, o quarto é seu.")+"";
				link.l1 = ""+GetSexPhrase("Você tomou uma boa decisão.","Bom garoto.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("É assim que é, né? Então, eu escolho o caminho difícil.","Sua vadia! Eu queria te tratar bem...")+"";
			link.l1 = ""+GetSexPhrase("Como quiser...","E você chama isso de 'gentilmente'? Tenho pena de você. Ou melhor, talvez não.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Tá bom, tá bom, chega! Não me mata. Eu tô indo embora.","Pare! O que a gente faz agora, se mata por causa desse quarto?! Engasga com ele, fica pra você. Fedorento...")+"";
			link.l1 = ""+GetSexPhrase("Decisão certa. Da próxima vez, pense melhor: nem todo mundo é tão generoso quanto eu, alguns podem te matar sem nem perceber.","Homens.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("Então, você me expulsou? Cai fora daqui antes que eu te corte.","Tudo o que você sabe fazer é tagarelar. Agradeça que ainda estou de bom humor, senão eu teria feito algo ainda pior com você. Agora suma daqui!")+"";
			link.l1 = ""+GetSexPhrase("Maldição...","Droga, te subestimei... Tá bom, tá bom, já tô indo.")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "Ah?.. Cai fora, novato, eu não bebo... hic!.. com qualquer um.";
			link.l1 = "Vou te dar um soco tão forte agora que você não vai conseguir beber por uma semana.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "O quê?! Sabe com quem está falando? Eu sou marinheiro do navio '"+pchar.ship.name+"! Só preciso avisar o capitão, e você não vai nem ter tempo de sair da cidade! Cai fora daqui enquanto ainda está inteiro."; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "Capitão?..";
			link.l1 = "Você vai esfregar o convés por um mês.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Desculpe, capitão!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "Saudações, capitão! Eu sei que você é o capitão, sim.";
			link.l1 = "Saudações. Como você sabe que eu sou o capitão?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ha, I am a seasoned sea wolf, I've been sailing the seas for more than a decade. I was mainly engaged in sailing: sailed in calm, in storms, on a lugger, and even on a battleship. True, last month I was wounded after a hard battle; there was a fierce storm and no one dared climb the sail, so I did, but I paid the price for it. Luckily, I only twisted my ankle and couldn't walk for a few weeks. So they sent me ashore. Now I'm better and I'm sitting here, waiting for an opportunity.";
			link.l1 = "Interessante. Eu não me importaria de ter um especialista nesse assunto. Gostaria de se juntar à minha tripulação?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "Por que não? Já sinto falta do convés do navio e do som das velas cheias de vento fresco. Posso até treinar sua equipe, se precisar. Mas já vou avisando: vou pedir mil pesos logo de cara, senão meus bolsos já estão vazios. Aliás, os bolsos do resto da equipe também. Sou uma pessoa honesta.";
			link.l1 = "Não, provavelmente vou recusar. Se eu pagar mil pesos para cada marinheiro embarcar, vou à falência. Não me culpe.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Fechado. Não me importo de pagar mil pesos por um bom especialista. Espere aí... aqui está. E vou te esperar no navio.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ha, sou um lobo do mar experiente, navego pelos mares há mais de uma década. Fiquei a maior parte do tempo junto aos canhões: disparei de falconetes, carronadas, colubrinas, sacres... servi num lugre e até num navio de guerra. É verdade, no mês passado fui ferido depois de uma batalha dura, um estilhaço de bala de canhão me acertou, nada grave, só um arranhão na perna, então me mandaram pra terra firme. Agora estou melhor e aqui estou, esperando uma oportunidade.";
			link.l1 = "Interessante. Eu não me importaria de ter um especialista nesse assunto. Gostaria de entrar para a minha equipe?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "Por que não? Já sinto falta do convés de artilharia, do cheiro de pólvora queimada e do estrondo das salvas de canhão. Posso até treinar sua equipe, se for preciso. Mas já vou avisando: vou pedir mil pesos, senão meus bolsos vão continuar vazios. E, como o resto da equipe, sou um homem honesto.";
			link.l1 = "Não, provavelmente vou recusar. Se eu pagar mil pesos para cada marinheiro embarcar, vou à falência. Não me culpe.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Fechado. Não me importo de pagar mil pesos por um bom especialista. Espere... aqui está. E vou te esperar no navio.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ha, eu sou um lobo do mar experiente, navego pelos mares há mais de uma década. Participei principalmente de abordagens: lutei contra piratas e exércitos regulares, sei manejar todo tipo de arma, servi em um lugre e até mesmo em um navio de guerra. É verdade, no mês passado fui ferido depois de uma briga feia, só um pequeno corte de sabre nas costas—o covarde não teve coragem de me enfrentar, mas acabei matando ele. Ah, você devia ter visto a cara deles quando viram o corte, ha-ha. Então me mandaram para terra firme. Agora estou melhor e estou aqui esperando uma oportunidade.";
			link.l1 = "Interessante. Eu não me importaria de ter um especialista nesse assunto. Gostaria de entrar para a minha tripulação?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "Por que não? Já sinto falta do som dos sabres, do estalo dos navios se aproximando e da adrenalina da batalha. Posso até treinar sua equipe, se for preciso. Mas preciso pedir mil pesos adiantados, pois meus bolsos já estão vazios. E, como o resto da equipe, sou um homem honesto.";
			link.l1 = "Não, provavelmente vou recusar. Se eu pagar mil pesos pra cada marinheiro entrar no navio, vou à falência. Não me culpe.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Fechado. Não me importo de pagar mil pesos por um bom especialista. Espere... aqui está. E vou te esperar no navio.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "Boa sorte no mar, capitão!";
			link.l1 = "Você também.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-quem é você?";
			link.l1 = "Eu sou o capitão "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Desculpa, camarada, estou com pressa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "Capitão?.. hic! C-capitão... me leva até a t-taverna... hic!.. hã? Por favor. Acho que... me p-perdi nessa c-colônia, é... hic!..";
			link.l1 = "Sai de cima de mim, não tenho tempo pra isso!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Certo, vamos lá. Não parece que você conseguiria chegar lá sozinho.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Só... hic!.. d-devagar, p-por favor. Eu estou... hic!.. não... consigo... ficar de pé...";
			link.l1 = "Certo, vamos, devagar.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "Capitão?.. hic!.. C-capitão... me ajuda!";
			link.l1 = "Sai daqui, não tenho tempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "O que há de errado com você?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Lá... na taverna... hic!.. o Trapaceiro!";
			link.l1 = "Ué, qual o problema nisso? Em qualquer taverna de qualquer colônia tem trapaceiros de cartas, feito sujeira.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "C-capitão, você... não entende... hic!... Ele me deixou... sem um único peso! Hic!.. E depois... me expulsou... hic!..";
			link.l1 = "E então, o que você quer de mim agora?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Vem c-comigo... hic!... Acaba com ele! F-faça... hic!... ele me devolver meu dinheiro! hic!..";
			link.l1 = "Você não precisa ser um mestre das cartas pra ganhar de um bêbado na mesa. Beba menos da próxima vez.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Bom, pra que eu preciso disso, hein? .. Tá bom, vamos lá, quero ver esse seu jogador de cartas.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Só... hic!.. d-devagar, p-por favor. Eu estou... hic!.. não... consigo... ficar de pé...";
			link.l1 = "Certo, vamos devagar.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "C-capitão... hic!.. muito obrigado... você me ajudou mesmo! Eu... aqui está... hic!.. É pra você.";
			link.l1 = "Vamos lá, deixa pra lá... Não beba assim de novo. Ou pelo menos, não vá procurar confusão.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "C-capitão!.. O... Hic!.. Trapaceiro de cartas!..";
				link.l1 = "Quem, eu? Trapaceiro de cartas?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "Lá está ele, capitão! Hic!.. S-sentado à mesa...";
				link.l1 = "Vamos lá...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "Não... hic!... O Sharper!... Ele sumiu!...";
			link.l1 = "Bem, ele foi embora, então não te esperou.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "E o que vem... d-depois? Hic!..";
			link.l1 = "Bem, agora não tem mais o que fazer. Eu é que não vou sair procurando ele pela colônia à noite. Não beba desse jeito de novo. Ou pelo menos não jogue quando estiver bêbado.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Que tal uma partida de dados? Topa?";
			link.l1 = "De jeito nenhum. Eu sou o capitão deste navio e não jogo com trapaceiros. Mas posso quebrar suas costelas facilmente se não devolver o dinheiro para aquele bom homem ali.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "Com trapaceiros?! Eu pareço um trapaceiro? Devolver o dinheiro pra quem, aquele bêbado?! Você me ofende, capitão...";
			link.l1 = "Posso ser mais agressivo. Devolva o dinheiro.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Sim, eu não sou trapaceiro! Jogo limpo. A sorte decide, e seu amigo só não teve sorte, só isso.";
			link.l1 = "Sorte, hein? Me dá seus dados e eu vejo se eles caem mesmo com tanta sorte.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "Tá bom, tá bom, calma aí, capitão. Olha, eu ganhei do bêbado, e trapaceei um pouco, mas é isso que todo mundo faz. Aqui está o dinheiro dele.";
				link.l1 = "Assim está melhor. E espero que você entenda que, se meu amigo disser que isso não é o valor completo, eu vou voltar aqui para falar com você?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Sim, por favor, aqui estão meus dados. Os dois conjuntos. Pode conferir. Não tenho nada a esconder.";
				link.l1 = "Então... Par... Nada... Par... Full... Nada... Nada... Dois Pares... Trinca... Nada... Par...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Sim, por favor, aqui estão meus dados. Os dois conjuntos. Pode conferir. Não tenho nada a esconder.";
				link.l1 = "Então... Quadra... Quadra... Full house... Full house... Quadra... Poker... Full house... Poker... Quadra... Full house... Hmm, e como você vai me explicar isso?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Entendi tudo, aqui está o valor completo. Boa sorte pra você e seu amigo.";
			link.l1 = "Você também.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "Mas... e-ele não queria admitir! Hic!..";
			link.l1 = "Sim, eu tentei evitar isso. Aqui, fique com seu dinheiro.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "C-capitão... hic!.. muito obrigado... você me ajudou mesmo! Eu...'vomita de lado'... aqui está... hic!.. É pra você.";
			link.l1 = "Ah, deixa pra lá... Não beba assim de novo. Ou pelo menos não aposte quando estiver bêbado.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "E então? Convencido?";
			link.l1 = "Hum, eles realmente parecem ser dados comuns ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Eu já disse. E seu amigo só está bêbado. Ele também não quis admitir a derrota, então trouxe você aqui.";
			link.l1 = "Tudo bem, desculpe pelo incidente. Boa sorte.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "Então... hic!.. o que foi?.. Ele... hic!.. não é um t-trambiqueiro?..";
			link.l1 = "Bem, parece que ele jogou limpo.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "E o que vem... d-depois? Hic!..";
			link.l1 = "Bem, agora não tem mais o que fazer. Ele te venceu, e foi justo. Não beba assim de novo. Ou pelo menos não aposte quando estiver bêbado.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Sorte. Você só teve sorte, só isso. A sorte é uma dama caprichosa.";
			link.l1 = "Hmm, é mesmo. Então vamos jogar, mas fique sabendo que eu jogo com estes dados!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "Esses?.. Quer dizer... Não, não quero brincar com você! Você me insultou. E além disso, estou sem um tostão...";
			link.l1 = "Talvez você queira que eu conte pra todo mundo nessa taverna sobre seus dados? Ou quem sabe mostrar pra eles? Aí você pode falar sobre sorte. O que acha?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "O quê?! Quem você pensa que é?! Tá tentando me chantagear?! Eu te encho de bala agora mesmo se não cair fora!";
			link.l1 = "Prefiro ficar aqui e mostrar seus dados para todo mundo.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "Então vem aqui, carniça!";
			link.l1 = "Não perca as calças.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "C-capitão?.. Você... hic!.. entrou numa briga?.. E esse aqui... hic!.. é mais afiado?";
			link.l1 = "Ele levou um soco. Não vai brincar com mais ninguém.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "Mas... e-ele não queria admitir! Hic!..";
			link.l1 = "Sim, ele tentou evitar. Ele simplesmente não tinha o seu dinheiro. Provavelmente já gastou.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Sim, ele tentou escapar. Aqui, seu dinheiro.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "E o que vem... d-depois? Hic!..";
			link.l1 = "Bem, agora não tem mais o que fazer. Ele te venceu, e foi justo. Não beba assim de novo. Ou pelo menos não aposte quando estiver bêbado.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "C-capitão... hic!.. muito obrigado... você me salvou! Eu...'vomita de lado'... aqui está... hic!.. É pra você.";
			link.l1 = "Ah, vamos... deixa pra lá... Não beba assim de novo. Ou pelo menos não aposte quando estiver bêbado.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "Capitão?.. hic!.. C-capitão... me leva até o c-cais... hic!.. hã? Por favor. Eu... hic!.. p-preciso ir para... o navio... O contramestre... vai xingar... hic!.. se eu me atrasar...";
			link.l1 = "Sai daqui, não tenho tempo pra isso!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Certo, vamos lá. Parece que você não consegue chegar lá sozinho";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Só... hic!.. devagar, p-por favor. Eu... hic!.. não... aguento...";
			link.l1 = "Certo, vamos devagar.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "C-capitão... hic!.. muito obrigado... você realmente me salvou! Eu... 'vomita de lado'... aqui está... hic!.. É pra você.";
			link.l1 = "Ah, deixa pra lá... Não beba assim de novo. Ou pelo menos, não vá atrás de confusão.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "C-c-capitão!.. Navio!";
			link.l1 = "Que 'navio'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "N-navio!.. Cadê ele?.. hic!..";
			link.l1 = "Obviamente ele foi embora. Você precisa beber menos nas tavernas. O navio inteiro não vai esperar por um marinheiro bêbado.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "Mas eu... hic!... não estou bêbado... quase... talvez...";
			link.l1 = "Ah, sim, de fato. Boa sorte.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "Espere, c-capitão! M-me leve... hic!.. para o seu n-navio! Eu não vou... hic!.. b-beber mais...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "Tá bom, fazer o quê. Mas vai direto pro navio. E Deus me livre de te pegar bêbado por aí, vai esfregar o convés até o próximo porto.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "Então você pode gastar meu salário ficando bêbado, e depois eu que tenho que sair te procurando em cada taverna e beco da colônia? Não, esse tipo de felicidade eu dispenso.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "Sim, c-capitão!.. hic!..";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "Capitão?.. hic!.. Você é... um rato de terra... hic!.. não é capitão!..";
				link.l1 = "Já derrubei centenas como você em abordagens, então cai fora, bêbado.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Capitão... hic!.. C-capitão daquele t-trambolho no ataque?.. hic!..";
				link.l1 = "Se você avistar este casco no horizonte enquanto estiver no mar, é melhor se jogar direto na água: suas chances de sobreviver com os tubarões são maiores do que enfrentando meu navio. Agora suma daqui!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "Capitão?.. hic!.. Você é um bebedor de leite, não um capitão!.. Sua m-mãe ainda era uma menina... hic!.. quando eu já navegava pelos mares...";
				link.l1 = "Mas sua mãe provavelmente ficaria feliz em saber que um garoto como eu virou capitão, enquanto você continuou sendo um marinheiro bêbado, bom só pra esfregar o convés.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "Capitão?.. Cuidado... hic!.. Capitão... vou quebrar seus dentes... hic!.. Você não vai ter tempo nem de piscar!..";
				link.l1 = "O recuo vai matar. Cai fora! Arranca meus dentes se tiver coragem...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "Capitão?.. Parece que... hic!.. u-um tipo de vagabundo...";
				link.l1 = "Parece que você ainda não se olhou no espelho...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "C-capitão?.. Eu não... hic!.. teria nem concordado em s-servir... no seu navio... hic!..";
				link.l1 = "E ninguém te convidou pra subir no meu navio, então você não tinha motivo pra aceitar. Sai da minha frente.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "Hic!..";
			link.l1 = "Vai dormir.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "Hic!.. Sim... ainda falta muito?.. ";
			link.l1 = "Estamos perto, tenha paciência.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-quem... hic!.. é você?..";
			link.l1 = "Sou o Capitão "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Desculpa, camarada, estou com pressa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "Capitão?.. hic!.. C-capitão... me ajuda! Eu... quero dizer... hic!.. meu amigo... precisa muito da sua a-ajuda! Por favor.";
			link.l1 = "Eu não vou resolver os problemas de todo bêbado que eu encontrar no meio da noite.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Certo, me conte o que aconteceu com seu amigo ali.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "Meu amigo ... bem, ele, no geral ... ele ficou bêbado. Só isso, no geral ... hic! .. ficou bêbado ...";
			link.l1 = "Claro, eu já fiz marinheiros sóbrios enquanto estavam de serviço, mas usei métodos bem radicais. Acho que seu amigo não precisa disso.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "Não! Ele... ele está com a g-guarda! Ele dis...cutiu com eles. E acabou brigando. E ele... hic!.. foi levado pra prisão... ele só está b-bêbado!";
			link.l1 = "E o que você quer de mim agora? A culpa é toda dele: devia beber menos. Ou pelo menos não sair procurando encrenca sozinho...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Fale com o carcereiro, cap... hic! .. capitão! Ele vai soltar... solta ele! Hmm... aqui está... hic!.. que sorte a sua... Meu amigo só... discutiu... bem... e quis me dar um soco na cara... mas... hic!.. não pegou nenhuma arma...";
			link.l1 = "Agora não me resta nada além de tirar bêbados da prisão à noite, depois que arrumam briga com os guardas. Não, deixa ele lá por uns dias. Da próxima vez talvez pense duas vezes antes de fazer isso.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Dane-se você. Tá bom, vou falar com o carcereiro.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "Não sei se o carcereiro vai gostar do meu sotaque. Ele só vai contar tudo pro governador depois. Então vai sem mim.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Receio, amigo, que o caminho para as masmorras locais esteja fechado para mim. O carcereiro guarda meu retrato como um santo, e não pretendo me instalar naquelas acomodações tão acolhedoras deles. Então, sinto muito, mas não posso te ajudar.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "O-obrigado... Capitão. E pelo meu a-amigo também. A-aqui... é para você.";
			link.l1 = "Da próxima vez, fique de olho no seu amigo quando ele se embriagar e resolver brigar com os guardas. Não é toda noite que capitães andam pelas ruas, prontos para negociar com o carcereiro por uns bêbados. Boa sorte.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "Oh!.. Então eu sei como... hic!.. libertar meu... a-amigo... hic!.. Guardas! Um e-espião na cidade!.. hic!..";
				link.l1 = "Você escolheu um jeito bem ruim de libertar seu amigo.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, e-estrangeiro... hic! .. Você... você vai ter problemas... hic! .. Tudo bem... eu tenho aqui... hic! .. está tudo sob controle.";
				link.l1 = "Claro. Se acontecer alguma coisa, vou procurar você imediatamente.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah ... então você ... hic! .. Você é um criminoso! Guardas!";
				link.l1 = "Ah, então é assim que você fala agora!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, como... hic! .. desculpa. E se... você me deixar... negociar por você com... hic!.. o carcereiro, e você... hic!.. pelo m-meu amigo?..";
				link.l1 = "Não, não precisa negociar por mim, obrigado. Boa sorte.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-q-quem... hic!.. é você?...";
			link.l1 = "Sou o Capitão "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Desculpa, camarada, estou com pressa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "Capitão?.. hic!.. C-capitão... escuta, me leva até a caverna perto da cidade... hic!.. hã? P-por favor.";
			link.l1 = "Para a caverna? Não entendi. Por que você vai para a caverna? E por que precisa de mim?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Veja... c-capitão... hic!.. Acabou meu d-dinheiro pra bebida... E em... hic!.. numa caverna eu tenho... um esconderijo, então... hic!.. Mas eu... é que... tenho medo de ir sozinho pela m-m-mata... hic!.. à noite... Então...";
			link.l1 = "Sai daqui, não tenho tempo pra isso!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Tá bom, vamos lá. Parece que você não consegue chegar lá sozinho";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "Só... hic!.. devagaaaar, p-por favor. Eu... hic!.. não... aguento...";
			link.l1 = "Certo, vamos devagar.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "C-capitão... hic!.. muito obrigado... você me ajudou mesmo! Eu... aqui está... hic!.. É pra você.";
				link.l1 = "Ah, vamos... deixa pra lá... Não beba assim de novo.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "Excelente, capitão! Fico feliz que tenha aceitado.";
				link.l1 = "Então, onde está o seu esconderijo? Espera aí, parece que você não está bêbado.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Sim, não bebi muito, não se preocupe comigo. E sobre o esconderijo... Galera!";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Pessoal, trouxe um esconderijo aqui. Vocês precisam abrir. A menos, é claro, que esse esconderijo se abra sozinho, de um jeito bom. Capitão, o que acha?";
			link.l1 = LinkRandPhrase("Acho que seria melhor se você bebesse até perder a memória. Pelo menos continuaria vivo. E agora só resta um caminho ... "," Acho que você não é muito esperto, já que resolveu roubar o capitão de um navio de guerra ... "," Acho que você deve estar cansado de viver, já que resolveu tentar isso... ");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "Certo, acho melhor sairmos em bons termos. E de quanto você precisa?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Então, não vamos abrir o esconderijo do jeito fácil?";
			link.l1 = "Receio que esse foi o último tesouro da sua vida.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "Ah, não somos gananciosos. Só "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "Receio que esse foi o último tesouro da sua vida.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "Tá bom, faça do seu jeito. Nunca mais vou ajudar um bêbado...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Capitão, você me surpreende com sua generosidade. Gostaria de compartilhar mais conosco?";
			link.l1 = "Já te dei tudo o que tinha. Estou indo embora...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-quem... hic!.. é você?...";
			link.l1 = "Eu sou o Capitão "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Desculpa, camarada, estou com pressa.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "Capitão?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... M-me desculpe... hic!.. pelo meu... e-estado. Quer se juntar a m-mim? hic!.. P-por favor."; 
			link.l1 = "Desculpa, "+GetAddress_Form(NPChar)+", mas estou ocupado."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Entrar? Desculpe, mas hoje não vou beber.."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "Ah, você não precisa... hic!.. b-bebê! É o seguinte... Bem... Eu já tomei um gole com meu amigo... Então... já estou meio tonto... entende?";
			link.l1 = "Certo. Então, você precisa de ajuda para ficar sóbrio?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "Na verdade, não! Eu tô bem. Agora eu quero j-jogar... cartas, no geral eu quero jogar... hic!.. M-mas não por esses míseros... p-pesos... com esses farrapos na... hic!.. t-taverna... Quero jogar com um verdadeiro cavalheiro! hic!.. Apostando de verdade!.."; 
			link.l1 = "Desculpe, "+GetAddress_Form(NPChar)+", o que posso dizer... Não sou fã de jogos de azar. Tem que pagar o salário dos marinheiros, manter o navio, sabe..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Hum, tudo bem, vamos jogar. Que tal irmos até a taverna?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "Tá bom! Só... hic!.. devagaaaar, p-por favor. Eu... hic!.. não... consigo... ficar de pé..."; 
			link.l1 = "Certo, vamos devagar."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "Por aquela mesa... hic!.. vamos!"; 
			link.l1 = "Certo, vamos."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "Você não faz... ideia, c-capitão, de como... hic!.. de como estou feliz em encontrar um verdadeiro nobre! hic!.. Neste fim de mundo... normalmente só... hic!.. g-gentalha..."; 
			link.l1 = "Sim, isso é comum nas colônias daqui. Então, vamos jogar?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "Sim, vamos jogar! Hic!.. Quais são as apostas?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "Estamos jogando por 1000 pesos."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "Estamos jogando por 2.000 pesos."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Hmm, desculpe, parece que meu bolso está vazio no momento..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "O-o quê?.. Você não tem... hic!.. dinheiro pra jogar... comigo?.."; 
			link.l1 = "Bem, acontece. Jogamos na próxima vez, não se preocupe."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "Hic!.. Foi uma noite e tanto, c-capitão! Hic!.."; 
			link.l1 = "Concordo com você. Pelo menos tire um tempo dos negócios."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "Hic!.. Foi uma noite e tanto, c-capitão! Hic!.."; 
			link.l1 = "Concordo com você. Pelo menos tire um tempo dos negócios."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "Às vezes a gente só precisa... hic!.. p-passar um tempo com uma... hic!.. boa companhia. Muito obrigado... hic!.. pela sua companhia!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "É, acabei de ser explodido em mil pedaços. E como é que você conseguiu ganhar até mesmo quando eu tinha tudo pra vencer?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Da mesma forma, obrigado pelo jogo e pela conversa."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "Às vezes a gente só precisa... hic!.. p-passar um tempo com uma boa... hic!.. companhia. Muito obrigado... hic!.. pela sua companhia!"; 
			link.l1 = "Da mesma forma, obrigado pelo jogo e pela conversa."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Só sorte, c-capitão... hic!.."; 
			link.l1 = "Isso não parece ser só sorte...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "O que você está insinuando? Está dizendo que eu trapaceei? Você viu tudo, nós pegamos as cartas do mesmo baralho!"; 
			link.l1 = "Sim, eu vi. E também vi que, há um minuto, sua língua mal se mexia, e agora você fala como se não estivesse bêbado."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "Ah, droga! E você me pegou direitinho! Tá bom, eu admito, não vou esconder. Eu não estava bêbado. Mas você sabe como é fácil enganar quem acredita nesses supostos ricos bêbados que querem jogar cartas? Todo mundo que tem algo pra apostar é quase o primeiro a correr pra taverna, sonhando em arrancar um bom prêmio de um nobre supostamente rico e bêbado. Deixa eu te dizer, você foi o primeiro a me enxergar de verdade."; 
			link.l1 = "E então, o que vai ser? Vai me devolver meu dinheiro do jeito fácil?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ha ha ha, não me faça rir, capitão. É claro que não vou te devolver nada! E nem pense que pode me obrigar. Posso muito bem fingir ser um nobre respeitado sendo insultado por um capitão qualquer. Então meu conselho pra você é: aceite sua derrota e vá embora."; 
			link.l1 = "Olha, espero sinceramente não te encontrar de novo em circunstâncias menos favoráveis, porque aí você não vai estar rindo assim. Adeus."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "E o meu conselho pra você é: tente arranjar um tempo pra conseguir uma espada."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "Você não teria coragem... É uma taverna, cheia de gente..."; 
			link.l1 = "Então eu sou só um capitão perdido, por que eu deveria me importar com regras de decência? E na taverna do porto à noite, o que poderia acontecer... Eu manejo a espada de um jeito muito melhor do que você."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "Ah, então é assim?! Pois agora vamos ver quem é o verdadeiro dono disso!"; 
			link.l1 = "A seu dispor..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "Capitão?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... M-me desculpe... hic!.. pelo meu... e-estado. Você pode me ajudar? hic!.. P-por favor."; 
			link.l1 = "Desculpa, "+GetAddress_Form(NPChar)+", mas estou ocupado."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Oh... ouvindo."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "É só que... Bem... Já estou meio tonto... Dá pra ver... hic!.. né?"; 
			link.l1 = "Para ser sincero, sim. Precisa de ajuda para ficar sóbrio?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "Na verdade, não! Eu tô b-bem. Quero uma mulher. Mas tô tão b-bêbado... hic!.. A m-madame vai me expulsar, então. Será que você... hic!... p-pode negociar por mim? Te dou dinheiro."; 
			link.l1 = "Desculpe, "+GetAddress_Form(NPChar)+", mas como posso te dizer... Eu não frequento bordéis. Honra, reputação... você entende ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Ah, tudo bem, eu vou te ajudar."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Só... hic!.. devagar, p-por favor. Eu... hic!.. não... aguento..."; 
			link.l1 = "Certo, vamos devagar."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "Aqui está o dinheiro... hic!... Vou esperar você a-aqui."; 
			link.l1 = "Ótimo, volto já."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "S-só... me traga... hic!.. o... melhor!.. Isso..."; 
			link.l1 = "Tá bom, tudo bem, eu entendi."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "Hic!.. Falta muito?"; 
			link.l1 = "A garota mais bonita desta colônia está te esperando lá em cima."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "Sim!.. Esta noite... está maravilhosa... O-o-obrigado, "+GetAddress_Form(NPChar)+". O resto do dinheiro... hic!... pega. E eu afundo... nos braços... da minha..... linda... daaaama...";
			link.l1 = "Então, aproveite."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Hic!.. Quanto tempo mais?";
			link.l1 = "Vou negociar em breve, tenha paciência.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "Hic!..";
			link.l1 = "Você precisa dormir.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "Hic!.. Sim... ainda falta muito?..";
			link.l1 = "Estamos quase lá, tenha paciência.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "Hã? Quem é você? O que está fazendo aqui?";
			link.l1 = "Eu poderia te perguntar o mesmo.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "Nós? Ah, nós... hum... Estamos colhendo flores aqui...";
			link.l1 = "Flores para túmulos? E como vai o seu herbário?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "Ela... Isso tem a ver com ervas?";
			link.l1 = "Então... Acho que entendi o que está acontecendo aqui.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "Não somos saqueadores! Não fale assim da gente! Nós só...";
			link.l1 = "O quê exatamente?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Bem, nós... Meu pai não deixa a gente se ver! E o pai dela também! Então nós... estávamos procurando um lugar sem testemunhas. Pra ficarmos sozinhos. De qualquer jeito, a fechadura da porta está quebrada, então é fácil entrar aqui...";
			link.l1 = "Agora entendo o que eram aqueles gemidos estranhos da alma inquieta...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Bom, se você já entendeu tudo, talvez agora nos deixe em paz?";
			link.l1 = "Você não tem medo de marcar encontros numa cripta? Não é o melhor lugar...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "Não somos supersticiosos! E mesmo que fosse assustador – que escolha a gente tem? Na cidade, nossos pais iam descobrir na hora. Mas aqui, ninguém vai dedurar a gente. Então, por enquanto, é a melhor opção.";
			link.l1 = "Me desculpe mesmo, mas será que você pode procurar outro lugar? Não me leve a mal, eu entendo — juventude e tudo mais — mas seus encontros quase mataram o vigia do cemitério de susto, com todos aqueles barulhos e gemidos vindo da cripta toda noite.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Bem... Assustar o guarda não fazia parte do nosso plano. Mas então, onde mais podemos nos encontrar? Ou você sugere que nossos encontros sejam ao ar livre?";
			link.l1 = "O amor não conhece limites. Procure outro lugar onde com certeza não vá incomodar ninguém. Assim ninguém vai incomodar vocês. Provavelmente. E é melhor resolver as coisas com seus pais – você não pretende se esconder pra sempre, pretende?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Fine, we'll think of something... We won't be scaring the guard anymore; you have my word.";
			link.l1 = "Maravilha. Boa sorte pra você!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "O quê?!";
			link.l1 = "Ah, nada...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou cidadão desta cidade e gostaria que você baixasse sua lâmina.","Escute, eu sou cidadão desta cidade e gostaria que você abaixasse sua espada.");
			link.l1 = LinkRandPhrase("Certo.","Como quiser...","Como você quiser...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
