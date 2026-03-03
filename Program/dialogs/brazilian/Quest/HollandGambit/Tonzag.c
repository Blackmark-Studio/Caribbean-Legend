// Эркюль Тонзаг, он же Плешивый Гастон
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Olá, "+pchar.name+".   Que bom ver que você está vivo.";
				link.l1 = "Gaston! É você?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Saudações, "+pchar.name+". Eu já sei dos seus negócios – o John me contou tudo. Nem sei o que dizer. Eu admiro você!";
				link.l1 = "Fico feliz em ouvir esse elogio vindo de você, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Boa tarde. Tem algum trabalho para mim?";
			link.l1 = "Não. Foi engano meu. Desculpe. Tchau. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Você me conhecia por esse nome. Mas meu verdadeiro nome é Hercule. Hercule Tonzag.";
			link.l1 = "Santo Deus! Também estou feliz em te ver... Não te reconheci no calor da luta. Você chegou bem na hora para ajudar.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Logo após a sua partida, recebi notícias de que Fleetwood havia reforçado a proteção de sua casa. Sugeri que poderia haver uma armadilha por trás disso. Imediatamente zarpei para Antígua no meu navio 'Twilight'—e, como você pode ver agora, por um bom motivo.";
			link.l1 = "É verdade. Mal consegui lidar com os guardas dentro da casa, mas estava exausto demais para continuar lutando na rua...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "Depois dessa briga, Fleetwood colocou um espião holandês na lista de procurados. Eles acharam que você era esse espião. Ele tem uma rixa antiga com eles. O pior é que um soldado na casa sobreviveu e se lembrou do seu rosto. Mas, de qualquer forma, isso já não é mais um problema. Eu terminei o que você começou. Esse soldado não vai reconhecer mais ninguém, e ninguém vai reconhecer ele...";
			link.l1 = "Você matou ele? Entendi...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Sim. Enquanto você estava desacordado na casa do John, eu feri o Fleetwood, mas o desgraçado conseguiu sobreviver. Deixei ele cego – joguei pimenta nos olhos dele e depois acertei antes que tivesse chance de sacar a espada. Mas o canalha estava usando uma cota de malha por baixo do uniforme – foi isso que salvou a vida dele. Esperto. Agora ele está de cama em casa, com a segurança reforçada. É uma pena que ele tenha sobrevivido.";
			link.l1 = "Então, sua principal missão em Antígua era eliminar Fleetwood?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Geralmente, sim. Mas agora parece impossível – a casa está sempre trancada, há meia dúzia de guardas escolhidos a dedo de plantão o tempo todo, e só deixam o confidente dele entrar – um velho artilheiro chamado Charlie, conhecido como Knippel.";
			link.l1 = "Já é alguma coisa...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Espere um pouco... Você vai se meter nesse assunto?";
			link.l1 = "Por que não? Você não precisa de ajuda? Você me salvou, e eu quero retribuir. Além disso, ainda estou precisando de dinheiro.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Por que não? Vocês são pessoas sérias. E pessoas sérias pagam bem. Só estou procurando um trabalho.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Acredite em mim, amigo, você não vai conseguir. Você é um sujeito de valor, realmente talentoso, e o diário de bordo que trouxe me ajudou a planejar um atentado contra o Fleetwood. Você lidou muito bem com os guardas – mas agora nunca vai conseguir chegar até o Fleetwood. Nem eu faço ideia de como fazer isso.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Vou pensar a respeito. Ainda tenho tempo. É uma pena que meu navio tenha sido apreendido, e que eu esteja sem tripulação.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Vou pensar nisso. Tenho tempo e um navio.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Acredite em mim, amigo, você não vai conseguir. Você é um sujeito de valor, realmente talentoso, e o diário de bordo que trouxe me ajudou a planejar um atentado contra o Fleetwood. Você lidou muito bem com os guardas – mas agora nunca vai conseguir chegar até o Fleetwood. Nem eu faço ideia de como fazer isso.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Vou pensar nisso. Ainda tenho tempo. É uma pena que meu navio tenha sido apreendido e eu esteja sem tripulação.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Vou pensar nisso. Tenho tempo e um navio.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Não se preocupe com isso. Quando seu velho barco foi apreendido, levei todos os seus oficiais e alguns marinheiros para o meu 'Crepúsculo'. Eles sabem que você está vivo e concordaram em continuar servindo. E, como recompensa pelo diário, estou passando meu navio, o 'Crepúsculo', para você.";
			link.l1 = "Obrigado! Vou me lembrar disso!";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Sim, eu gostaria de pagar pelo diário. 15.000 pesos – infelizmente, não tenho mais do que isso no momento. Vamos acertar tudo em um dia. ";
			link.l1 = "Não precisa. Isso já basta. Se você não tivesse chegado a tempo, eu não ia precisar de dinheiro nenhum, de qualquer jeito.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Certo, "+pchar.name+", eu preciso ir. Ainda não vou voltar para Bridgetown. Se algum dia precisar de mim - fale com o John. Boa sorte!";
			link.l1 = "Boa sorte, Hercule!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			DialogExit();
			AddDialogExitQuestFunction("HollandGambit_NewShipTwilight");
		break;
		
		case "SJ_talk_11":
			dialog.text = "Gostaria de lhe entregar esta armadura por ter eliminado Fleetwood. Ela vai te proteger nas próximas batalhas. Vamos ver o John agora. Ele quer conversar com você e te fazer... uma proposta interessante.";
			link.l1 = "Obrigado pelo presente. Certo, vamos...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Eu também gostaria de conversar com você, capitão. Eu ia lhe ensinar meu ofício, mas agora vejo que sou eu quem deveria aprender com você. Me contrate como oficial no seu navio – você não vai se arrepender.";
			link.l1 = "Com prazer, Hercule! Seja bem-vindo à tripulação!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, não consigo me imaginar como seu superior. Agradeço sua oferta, mas simplesmente não consigo vê-lo como meu subordinado.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1":
			ForceHeroAutolevel(npchar);//Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Como quiser, "+pchar.name+". Até logo. Talvez nos encontremos de novo. Foi um prazer trabalhar com você.";
			link.l1 = "Boa sorte, amigo!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Estou ouvindo, capitão. O que você tem a dizer?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Você está com um semblante sombrio, capitão. Aconteceu alguma coisa?";
				Link.l1 = "Preciso deixar o arquipélago. Daqui a duas semanas. Em um navio de outro, como passageiro.";
				Link.l1.go = "SharlieEpilog_Tonzag_1";
				break;
			}

			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, eu vou para a antiga cidade indígena de Tayasal e, o que é ainda mais estranho, meu caminho passa por uma estátua de teletransporte. Vai comigo?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, me dê um relatório completo sobre o navio.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Quero que você compre certos produtos toda vez que atracarmos.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Cheguei como ordenado, Capitão.";
				Link.l2 = "Preciso lhe dar várias ordens.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ouçam minhas ordens!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nada no momento. Pode relaxar!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Capitão, me desculpe, mas eu não mexo com números e cálculos. Pergunte ao van Merden – ele tem jeito pra essas coisas, embora eu duvide que ele queira sair do seu canto.";
			Link.l1 = "Você tem razão, Hercule. Ah, preciso arrumar um intendente pra mim...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Capitão, quando eu era estalajadeiro em Barbados, eu só comprava rum e mantimentos. E por mantimentos, quero dizer comida de verdade, não só biscoitos e carne salgada. Desculpe, mas essa parte não é comigo.";
			link.l1 = "Talvez devêssemos transformar meu navio em uma taverna... Brincadeira, Hercule. Deixa pra lá, eu faço isso sozinho.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Estou ouvindo você.";
			Link.l1 = "Isso é sobre abordagens.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Isso é sobre o seu navio.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nada até agora.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Então, qual é o seu desejo?";
			Link.l1 = "Não aborde navios inimigos. Cuide de si mesmo e da tripulação.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Quero que você aborde navios inimigos.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Então, qual é o seu desejo?";
			Link.l1 = "Eu prefiro que você não troque seu navio por outro depois de embarcar. Ele é valioso demais.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando você embarca em navios inimigos, pode reivindicá-los para si, se forem bons o bastante.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
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
			dialog.Text = "Aye-aye.";
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
            dialog.Text = "Quais são suas ordens?";
            Link.l1 = "Fique aqui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Me siga e não fique para trás!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mude o tipo da sua munição.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Escolha do tipo de munição:";
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Aye!";
            Link.l1 = "À vontade.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aye!";
            Link.l1 = "À vontade.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Você é um filho da mãe de sorte, capitão. Ainda bem que me juntei a você naquela época, quando eu, você e o John trabalhávamos juntos. Que um tubarão me engula se eu não te apoiar nessa empreitada!";
			link.l1 = "Obrigado, Hercule! Fico feliz que eu estava certo sobre você.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Então, quando vamos partir?";
			link.l1 = "Daqui a pouco. Agora devemos nos preparar para a viagem.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Praticamente nada, chefe. Se isso tivesse a ver com nossos negócios, já teriam nos colocado na mesa de tortura.\nComo não nos levaram para interrogatório imediatamente, o assunto aparentemente não é urgente.\nOu é uma armação ou chantagem.\nVão deixar a gente aqui de molho por alguns dias sem explicar nada. Depois vão aparecer com uma proposta que a gente vai ter que aceitar.";
			link.l1 = "Experiência pessoal?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Bem, existe alguma maneira de fazer com que eles venham com uma proposta dessas agora?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Claro. Gruoh já foi paga pelos parentes de um homem morto para poupá-lo das carícias de despedida do carrasco de Trinidad.\nEla pagou ao comandante pelo direito de circular pelas celas. Prática comum – muitos pagam aos soldados para poder atormentar quem não pode se defender, sem testemunhas.\nO homem morreu em silêncio, sem sofrimento. Trabalho limpo e decente.";
			link.l1 = "Gruoh? Quem é esse?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Desculpa, chefe. Lugar errado, hora errada.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Podemos tentar. Vamos esperar a hora da comida, e eu troco umas palavras com o sentinela. Sabe, eles ainda não aprenderam a revistar direito. É...";
			link.l1 = "O que foi?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Que sensação estranha, capitão. Eu diria até que é um pressentimento. Com licença, vamos conversar depois.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Perdi alguma coisa, capitão?";
			link.l1 = "Ah, nada de especial, só mais um dia no mar. Olha só pra você, seu velho safado! Você fez uma bela bagunça aqui pra mim.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "O sangue sai com água fria, Capitão. Precisamos conversar.";
			link.l1 = "Acha? Não faria mal sobreviver a este dia, pra começar.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Também estou feliz em te ver, Rumba. Capitão, não vou te incomodar agora, conversamos depois.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Oi, Ruivo. Capitão, não vou atrapalhar, conversamos depois.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Capitão, não vou te incomodar, conversamos depois.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Pronto para me ouvir, Capitão?";
			link.l1 = "Já passou da hora de conversarmos, Hercule. Acabei de perceber que eu quase não sei nada sobre você.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Então está na hora de nos conhecermos. Vamos pular os primeiros anos, até porque não tem nada ali pra contar – um soldado vitorioso, um derrotado, um desertor, um saqueador... você sabe como é.";
			link.l1 = "Na verdade, não, mas até agora isso parece bem comum.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "As oportunidades de carreira depois de uma trajetória militar dessas eram poucas para mim – bandido, enforcado ou guarda digno da Companhia Holandesa das Índias Ocidentais. Escolhi a última, como você pode imaginar.";
			link.l1 = "Você também desertou de lá?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Pelo contrário, fiz carreira lá. Recebi uma proposta para entrar na ala de combate do departamento de inteligência da Companhia, onde conheci minha futura esposa.";
			link.l1 = "Ok, até agora a história está bem tranquila... especialmente se você não pensar muito nos métodos dos holandeses.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Você não vai ganhar muito dinheiro sendo honesto, e existem várias formas de lidar com a concorrência. Sim, nós agíamos com métodos especiais...";
			link.l1 = "Acho que entendi o que você quer dizer...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Sim, podia ser qualquer coisa: de pirataria a incendiar armazéns cheios de mercadorias. No fim, o esquema foi descoberto e fomos dissolvidos... no papel, é claro. Foi assim que nasceu a Liga, conhecida e controlada apenas pelos líderes escolhidos das altas esferas da Companhia. Para um fora da lei caribenho de verdade, só havia duas opções: pirataria ou a Liga. E a Liga geralmente pagava melhor\nNa maioria das vezes, a Liga ainda trabalhava para os holandeses, mas também podia aceitar trabalhos paralelos...";
			link.l1 = "As coisas estão começando a clarear...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "A Liga estava por trás daquela farsa em Tortuga. E depois aquele grupo de desembarque...";
			link.l1 = "Eu já imaginava. Mas por quê?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Porque ninguém sai vivo da Liga, e você não pode simplesmente escapar impune das coisas que fizemos lá, Capitão. Eu queria me aposentar, então tentei mesmo assim. Como pode ver, não tive muito sucesso.";
			link.l1 = "Você está dizendo que seus antigos colegas gastaram uma fortuna, sacrificaram quase cem pessoas, queimaram um navio incendiário e arriscaram o navio de guerra deles só para... matar você por deserção?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "Eu fui mais do que só um peão na Liga, Capitão. Sei demais sobre eles. Eles não podem simplesmente me deixar ir, e precisam deixar isso bem claro, pra que ninguém mais pense em sair do negócio... Já tentaram me pegar antes... faz muito tempo... Mataram minha esposa e me desfiguraram, mesmo que isso tenha custado caro pra eles. Não existe final feliz nessa história, Capitão. É só dar a ordem, e eu deixo o navio e encaro eles sozinho, pela última vez.";
			link.l1 = "Não fale besteira, Hercule... E que papel Lucas Rodenburg teve em tudo isso? Ele deve ter estado envolvido nessas questões! A sua, ou melhor, a 'organização' dele, a Liga...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Agências diferentes, Capitão. É verdade que muitas vezes obedeciam à mesma pessoa e trabalhavam lado a lado. Mas os agentes especiais do Rodenburg agiam com precisão e eficiência, enquanto a Liga fazia operações em massa. E agora, o que restou da Liga? A organização não existe mais, como pode ver: estou aqui com você, John Murdock foi embora, Longway fugiu, Van Berg está no fundo do mar, Rodenburg foi executado... Ainda assim, eu devia ao falecido canalha. Ele me notou na Liga e, quando tentei sair, me tirou de uma enrascada séria e me fez seu braço direito. Claro que os outros não gostaram, mas ninguém ousava desobedecê-lo... E então, nas circunstâncias que você conhece, ele resolveu se livrar de Murdock e de mim, mas você interveio e me tomou para o seu serviço. E aí pensei: 'Está aí minha segunda chance de romper com o passado...' Você superou Rodenburg, a Liga perdeu seu protetor, o perigo tinha acabado... Mas, claro, eu estava enganado... Velho tolo... Mas chega disso, Capitão. Vamos pensar no que fazer agora, se é que você realmente não pretende me largar no primeiro porto.";
			link.l1 = "Eu não. Suponho que você tenha um plano?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Nada de especial, na verdade. Nunca vamos acabar com todos eles, mas podemos causar perdas tão grandes que não vai valer a pena continuarem vindo atrás de mim... de nós.";
			link.l1 = "E como fazemos isso? Eles têm um acampamento?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Uma grande fortaleza? Difícilmente. Seria muito chamativa e perigosa para a Liga. E por perdas, não falo de vidas humanas – eles não ligam para pessoas, mas não gostam de perder ouro. O dinheiro da Companhia não chega mais para eles, certo? Duvido que a Liga tenha encontrado um novo patrono, então devem estar arrancando ouro de outro lugar.";
			link.l1 = "E que lugar seria esse?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Não sei, capitão.";
			link.l1 = "Hercule, mas você acabou de dizer que está sendo perseguido justamente porque sabe demais!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Deixe-me pensar... Talvez a Liga esteja agindo contra os espanhóis no momento. Eles são os principais candidatos para uma boa reviravolta. Aliás, o Rodenburg sempre se deu bem com os figurões castelhanos. Às vezes ele mandava os rapazes da Liga fazer uns trabalhos pra eles e sempre proibia qualquer coisa que pudesse prejudicá-los, o que, aliás, os rapazes não gostavam nem um pouco...";
			link.l1 = "Boas relações, é? E aquele tal de hidalgo e o dedo dele, que você me fez arrastar até a sua taverna?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "Isso foi um caso especial, um serviço à parte. Se está se sentindo culpado, capitão, pode ficar tranquilo – aquele Don teve o que merecia... Mas estou falando de outra coisa: depois que o chefe deles sumiu, os agentes da Liga podiam simplesmente ter seguido seus próprios interesses e tentado abocanhar uma boa fatia do bolo espanhol. Graças ao trabalho com os espanhóis sob o comando do Rodenburg, eles sabem exatamente onde e o que pegar.";
			link.l1 = "Hm... talvez você tenha razão. Mas pelo que eu sei, ninguém realmente invade bancos espanhóis, atacar os espanhóis no mar já é coisa de sorte... Talvez devêssemos procurar algum empreendimento espanhol? Uma fábrica?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Uma suposição razoável, capitão... Temos mais alguma pista?";
			link.l1 = "Hm... o navio que nos atacou hoje foi para o sul...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "É improvável que o capitão deles volte a nos incomodar, mas ele deve avisar os outros que as coisas não saíram como planejado, e talvez levar a tripulação para outro lugar. Mais alguma coisa?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Sim, tive uma conversa amigável com o comandante da prisão de Tortuga... Ele mencionou algo sobre o continente.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "Não, nada mais.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Excelente, capitão! Sul, continente, espanhóis – isso significa que vamos encontrá-los rápido. Vamos zarpar? E obrigado por ouvir minha história.";
			link.l1 = "Sim, acabamos mesmo tendo uma conversa de coração para coração... Vamos zarpar!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Não é muita coisa para se basear. Mas para gente como nós, isso já basta. Vamos para o sul? Procurar uma companhia comercial espanhola? E obrigado por ouvir minha história.";
			link.l1 = "É, acabamos tendo uma conversa bem sincera, hein... Vamos zarpar!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Olha, Capitão. É assim que eles agem.";
			link.l1 = "E você também trabalhou assim?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Vamos lá, ver o que tem dentro.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Um caso sórdido, capitão. Limpamos esse covil, mas com certeza não será o último...";
			link.l1 = "E a mina, Hercule?! E todas aquelas pessoas lá fora?! Elas também foram 'eliminadas'?! E o que aquele canalha quis dizer com isso?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Let's discuss this later, Captain. Their commander survived; we need to interrogate him.";
			link.l1 = "E se ele não souber de nada?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "He knows something. Think about it - they were waiting for us, carried out all the gold, and eliminated witnesses. That means they had a plan. I want to take a look around here, and later I'll bring the scoundrel to the ship myself. You should also keep an eye out; perhaps they were too hasty and missed something.";
			link.l1 = "Certo, mas quando voltarmos para o navio, precisamos ter uma conversa séria!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Boas notícias, capitão.";
			link.l1 = "Não vejo nada de bom na nossa situação, Hercule. Vamos, precisamos conversar a sós.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Então é assim, né? Certo, Capitão.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Vejo que vamos ter uma conversa séria, capitão.";
			link.l1 = "Sim, e serei eu quem vai falar. Para começar, você não acha que tem um certo padrão se formando aqui? Pilhas de cadáveres nos seguem por onde passamos! Primeiro, você leva uma saraivada de balas no estômago, e no dia seguinte mais de cem pessoas, boas e nem tão boas, morrem em... nem posso chamar aquilo de batalha naval! Uma vila foi varrida do mapa há poucos dias, e hoje nós mesmos aumentamos essa pilha matando um monte de gente nas minas.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Naturalmente, me preocupa a possibilidade dessa pilha virar uma montanha amanhã, mas o que realmente me assusta é que todo esse sangue está sendo derramado por causa de uma só pessoa. E essa pessoa ocupa um cargo importante na minha tripulação!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "Segundo, você mentiu pra mim, Hercule. Nenhum desertor vale o esforço que seus antigos colegas estão fazendo pra te eliminar. O que nosso prisioneiro gritava nas minas? Traidor? Porto Bello? Gruoch? Você aprontou alguma coisa, Hercule, e dessa vez eu quero a verdade.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Truth? The truth is, Captain, that I did desert, along with my wife Gruoh. Madame Tonzag didn't want to leave the League; she loved that life, but she loved me even more. We were supposed to take care of a Spanish hidalgo, but he made a better offer. It was our chance, and we both agreed to go into his service. Of course, the League thought we perished on a mission and sent a second group to Porto Bello to finish the job and seek revenge.";
			link.l1 = "E você matou todos eles?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "Primeiro, mataram o Gruoh e me desfiguraram. O fidalgo não quis mais saber de mim e me expulsou. Foi aí que o Rodenburg me encontrou...";
			link.l1 = "E como eu deveria confiar em você agora? Você desertou do exército, abandonou a Liga e matou seus próprios parceiros! Quando chegar a hora certa, vai me trair também?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Sim, eu desertei, quebrei o contrato, matei umas duas dúzias de membros da Liga. Mas aprendi a lição, Capitão. E além disso, um homem morto não pode trair ninguém, e eu estou morto há muito tempo, desde Porto Bello. Talvez seja por isso que agora é tão difícil me matar.";
			link.l1 = "Já chega por hoje. Sinto que você ainda não está me contando tudo.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Eu mesmo vou cuidar do prisioneiro, ou você quer participar?";
			link.l1 = "Vamos. Eu mesmo vou interrogá-lo.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "Não, esse tipo de assunto não é pra mim. Te vejo na minha cabine em meia hora!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Quem está no comando agora? Arno?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "Aquele canalha chegou ao poder? Não demorou muito para vocês virarem uma quadrilha qualquer de bandidos...";
			link.l1 = "Quem é Austin?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "A gangue do Austin ficou famosa por atrair capitães livres para o mato, esquartejá-los e arrancar até o último tostão ou bugiganga dos corpos. Era um bom negócio, e como nunca faltavam aventureiros, ninguém se importava. Mas eles se deram mal com um capitão, então ele teve que se abrigar sob as asas da Companhia. Mantivemos ele sob controle e só soltávamos quando precisávamos resolver algum problema de forma rápida e simples.";
			link.l1 = "Duvido que eu consiga negociar com uma pessoa dessas.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "Com certeza. Se ele e o pessoal dele estão no comando agora, logo a Liga vai virar só mais uma quadrilha.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "Foi uma conversa interessante.";
			link.l1 = "Eu gostaria de saber o quanto disso é verdade... E sobre o massacre em Porto Bello? Se ele não estava mentindo, isso significa que da última vez que conversamos, você mais uma vez deixou de fora alguns fatos importantes da sua ilustre biografia.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "Fez um calor infernal em Porto Bello, Capitão. Lutei pela minha vida, pela vida do meu patrão, pela vida da minha esposa. Não tive tempo de contar os mortos ou lamentar cada camponês que estava na rua na hora errada.";
			link.l1 = "Nessa ordem de prioridade?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "Não, claro que não. Primeiro o dela. Sempre.";
			link.l1 = "O que acha? Vamos para Caracas?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Eu, pessoalmente, não iria, Capitão. E também aconselho você a não ir. Para a Liga, você já não é mais um inimigo, e eu não sou de interesse deles, pelo menos por enquanto, enquanto estiver ao seu serviço. Além disso, tenho um pressentimento ruim lá no fundo\nVai ser ruim se formos lá. Muito ruim. Essa história não tem um final feliz. Mas estarei com você até o fim, Capitão.";
			link.l1 = "Vou pensar nisso.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "Aliás, você tinha razão – eles não conseguiram limpar a mina direito. Olha.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Um diário de oficial... criptografado, mas é uma cifra antiga, eu conheço\nNada de interessante, ao que parece. Era o diário do nosso prisioneiro. Agora está claro por que ele estava tão disposto a falar. Veja aqui – indícios de um tesouro escondido! O canalha claramente planejava se aposentar e estava pronto para fugir a qualquer momento!";
			link.l1 = "E onde fica esse lugar escondido?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "Você conhece aquela ilha, Capitão. Nessas águas, você acabou com Van Berd.";
			link.l1 = "Certo, não fica muito longe, então vamos dar uma olhada. Quanto a Caracas, ainda não decidi, mas acho que temos um mês.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Como quiser, Capitão. Estou com você até o fim.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "It's done, Captain. Austin is currently in Caracas; I think we have a month.";
			link.l1 = "Primeiro as coisas mais importantes. O que o prisioneiro disse? Quem é esse Austin? E por que devemos ir para Caracas?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "A gangue do Austin ficou famosa por atrair capitães livres para o mato, matá-los e arrancar até o último centavo ou bugiganga dos cadáveres. Era um bom negócio, e como nunca faltavam aventureiros, ninguém se importava. Mas eles se deram mal com um capitão, e por isso ele precisou colocar a tripulação dele sob a proteção da Companhia. Mantivemos ele sob controle e só soltávamos quando precisávamos resolver algum problema de forma rápida e direta.";
			link.l1 = "Duvido que eu consiga negociar com uma pessoa dessas.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "Isso é certo. Se ele e o pessoal dele estão no comando agora, logo a Liga vai virar só mais uma quadrilha. Mas eu não iria para Caracas, Capitão.";
			link.l1 = "Sério? Está com medo?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "Não é bem assim, Capitão. Antes de morrer pelos ferimentos, o prisioneiro revelou que você não é mais inimigo da Liga, e que eu não interesso mais a eles, pelo menos enquanto eu estiver ao seu serviço. Parece que a Liga agora tem algum novo patrono influente que mandou nos deixarem em paz\nE Caracas... Eu tenho um pressentimento ruim, lá no fundo... Vai ser ruim se formos pra lá. Muito ruim. Essa história não vai terminar bem. Mas estarei com você até o fim, Capitão.";
			link.l1 = "Vou pensar nisso. Claro, eu gostaria de resolver essa questão de uma vez por todas, mas talvez você tenha razão. Duvido que, depois dos acontecimentos da semana passada, eles se atrevam a se aproximar de nós novamente.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "Aliás, você estava certo – eles não conseguiram limpar a mina direito. Olhe.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Um diário de oficial... está criptografado, mas é uma cifra antiga, eu conheço\nNada de interessante, ao que parece. Era o diário do nosso prisioneiro. Veja aqui – indícios de um tesouro escondido! O canalha claramente planejava se aposentar e estava pronto para fugir a qualquer momento!";
			link.l1 = "E onde fica esse lugar escondido?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "Você conhece aquela ilha, capitão. Nessas águas, você acabou com Van Berd.";
			link.l1 = "Certo, não fica muito longe, então vamos dar uma olhada. Quanto a Caracas, ainda não decidi, mas acho que temos um mês.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Como quiser, Capitão.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Espere aí, capitão. Eu vou sozinho.";
			link.l1 = "And why is that? Feeling heroic now? It's too late; you've made this mess, but we have to clean it together.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Não precisa pagar pelos meus erros, Capitão. Você estava certo – onde quer que eu vá, pessoas morrem e sangue inocente é derramado. Se entrarmos juntos naquela igreja, vai ser outro Porto Bello, e eu não quero isso.";
			link.l1 = "O que realmente aconteceu lá?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Um massacre. Eu queria me aposentar, Capitão. Queria pegar o ouro, minha esposa e voltar para casa, em Carcassonne. Eu sabia que a Liga mandaria mais gente para terminar meu serviço, então aceitei um adiantamento generoso do meu novo patrono. Depois, só faltava colocar a guarda da cidade contra meus antigos comparsas e o novo patrão. No meio daquela confusão, eu sumiria com o dinheiro e, talvez, se desse tempo, ainda roubasse uns ricaços de Porto Bello.";
			link.l1 = "Bom plano, embora eu tivesse feito de outro jeito. Tem coisas demais que podem dar errado.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Eu também não sou nenhum santo, mas o seu jeito me faz até arrepiar. Me surpreende você ainda não ter me traído, como fez com a Liga, o Hidalgo e até com a sua própria esposa.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Everything that could go wrong, did go wrong. Shooting a three-pounder towards the governor's palace was a mistake. It barely scratched the governor himself, but his beautiful daughter, as I hear, had to have both her legs amputated below the knees to save her life. The response was horrific - a blood bath; great many people perished, Captain. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Explique.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Se Madame Tonzag ainda estivesse viva, eu teria te traído sem hesitar, capitão. Sou um homem morto andando, te seguindo porque não tenho outro lugar neste mundo. Agora você está olhando para a última testemunha viva daqueles acontecimentos, e não faz muito tempo, você mesmo eliminou outra.";
			link.l1 = "Explique.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Me perdoe, Capitão, por não ter contado tudo desde o começo. Quando nos conhecemos, achei que você fosse só mais um canalha como eu. E sabe qual foi a primeira coisa que fiz? Mandei você limpar minha sujeira – matar aquele Don espanhol que, a princípio, eu não queria matar, mas depois resolvi trair. Aquele hidalgo, Rodriguez...";
			link.l1 = "E para que você precisava do dedo dele?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Sem truques aqui. Só um teste, Capitão. Recrutamos dezenas de jovens canalhas como você todo ano. Só alguns passam no teste básico de honestidade, e mesmo esses morrem nas primeiras operações. Você não era para ter sobrevivido à missão com o diário de bordo do Fleetwood. Eu planejava simplesmente entrar na casa, acabar com os sobreviventes e pegar o diário.";
			link.l1 = "Se não me falha a memória, a história tomou um rumo um pouco diferente.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "Foi isso mesmo, Capitão. Não sei o que me levou a te ajudar, mas você lutou contra os Raposas com tanta vontade de viver que até me contagiou, mesmo que por um instante. No fim das contas, sem saber, você me salvou. Você não me deve nada, Capitão. E não vou deixar você entrar lá. Isso é comigo, é a minha redenção.";
			link.l1 = "Como quiser, Hercule. Dói perder um lutador assim, mas você se perdeu faz tempo, e não vale mais sangue derramado. Você também não me deve nada, e espero que encontre redenção naquela igrejinha.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Bela fala, Hercule. Vai pro inferno! Caso não tenha notado, seus problemas viraram meus ultimamente. Você é meu oficial, e só eu decido se merece perdão ou não. Então vai ter que ficar conosco mais um tempo e conquistar sua redenção com coragem como parte da minha tripulação!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Obrigado por tudo, capitão. Adeus!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Sim, senhor, Capitão!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "Já vi muitos canalhas na minha vida, Capitão, mas foi a primeira vez que senti um calafrio de horror por dentro. O que você acha: se um monstro menor mata um monstro maior, isso conta como redenção?";
			link.l1 = "Será que eles misturam rum com água? Me avise quando descobrir. Vamos, já terminamos aqui.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;
		
		// Эпилог
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Ha! Essa eu não esperava ouvir de você. Vai se juntar a um mosteiro também?";
			link.l1 = "Estou falando sério, "+npchar.name+". A saúde do meu pai piora a cada dia. Quero vê-lo antes que... seja tarde demais.";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "E o que tem de errado com nosso navio? Ou você acha mesmo que o Atlântico agora é demais pra nós?";
			link.l1 = "Tenho pensado em desembarcar e levar uma vida mais calma. Ainda não sei como é viver longe do mar. Mas se esse dia realmente chegar, quero estar preparado. Quero entender a luta que vai acontecer dentro de mim.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Segunda vez que me pega de surpresa nessa conversa. Vai trocar o vento nas velas por lareira e mingau quente, é isso?";
			link.l1 = "A piora da doença do meu pai me fez lembrar que ninguém é eterno. Mas ainda não decidi o que virá depois. Por agora — só o caminho de volta pra casa. E... queria te convidar a vir comigo. Como amigo. Mas se disser não — eu entendo. Não vou insistir.";
			link.l1.go = "SharlieEpilog_Tonzag_4";
		break;

		case "SharlieEpilog_Tonzag_4":
			dialog.text = "Recusar? Que eu passe o resto da vida limpando âncora se deixar você ir sozinho! Não me conhece nada, capitão.";
			link.l1 = "Era exatamente a resposta que eu esperava. A velha França já não é mais a mesma. Está vazia, entediante, estranha... E duvido que tenha sobrado alguém lá que eu possa chamar de amigo. Dentro de duas semanas partimos, e não pretendo perder tempo. Vamos fazer uma bela festa na taverna pra comemorar. Que me diz?";
			link.l1.go = "SharlieEpilog_Tonzag_5";
		break;

		case "SharlieEpilog_Tonzag_5":
			dialog.text = "Ha! Se acha que vou recusar isso — tá sonhando!";
			link.l1 = "Então tá decidido — nos vemos na taverna assim que eu cuidar do resto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tonzag_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tonzag = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;

	}
}