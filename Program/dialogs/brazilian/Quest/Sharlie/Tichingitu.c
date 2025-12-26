// Тичингиту - индеец-офицер
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
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "O que você quer, cara-pálida? Tichingitu não tem nada a dizer para você.";
			link.l1 = "Seu nome é Tichingitu? Hm. Escute, guerreiro, não vim aqui para ficar te encarando. Vim aqui para te fazer uma pergunta: Por que você invadiu a casa daquele homem gordo?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Não vai dizer nada? Não é uma boa ideia. Vão te enforcar por roubo e por tudo mais que você fez. Me diga por que cometeu esse ato e talvez eu consiga te ajudar.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu chegou à cidade dos rostos pálidos por muitos, muitos caminhos, atravessando grandes águas, vindo de florestas e pântanos imensos. Tichingitu estava cansado e queria comer. Tichingitu estava morrendo de fome. Ninguém queria ajudar Tichingitu. Gritaram: 'Vá embora, cachorro de pele vermelha.' O dono da taverna expulsou o índio como se fosse um cão sarnento. Tichingitu queria comer.";
			link.l1 = "Maldição, mas por que você veio para este povoado saindo... da sua floresta?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu foi expulso da tribo indígena. Tichingitu brigou com o xamã da tribo, o xamã contou tudo ao chefe, lançou uma maldição sobre Tichingitu, e Tichingitu deixou a tribo, indo para bem longe da sua terra natal. Tichingitu não tem casa, não tem arma, não tem nada.";
			link.l1 = "Isso é o que eu chamo de azar. Por que você brigou com os seus próprios companheiros?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "O xamã da tribo é um homem cruel. Ele disse que um espírito maligno havia possuído o corpo da minha esposa. Minha esposa precisava morrer. Mas ela só estava doente, não havia espírito nenhum nela. Tichingitu tentou cuidar dela, mas o xamã a matou. Tichingitu enfrentou o xamã, então todos se voltaram contra Tichingitu, e ele foi embora.";
			link.l1 = "Você tentou salvar sua esposa? Foi por isso que te expulsaram da vila?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Sim, cara-pálida. Tichingitu não tem escolha. Ou rouba, ou morre de fome...";
			link.l1 = "Olha, sinceramente... Enforcar alguém por umas poucas moedas roubadas por um homem faminto... Tichingitu, vou tentar te ajudar. Conheço o Fadey, aquele brutamontes na casa de quem você entrou escondido. Talvez eu consiga fazer alguma coisa... Vou falar com o comandante.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_1");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu espera. Índio não teme a morte. O xamã amaldiçoou Tichingitu, Tichingitu deve morrer.";
			link.l1 = "Nem tudo está perdido ainda. Vou tentar ajudar...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu espera. Índio não teme a morte. O xamã amaldiçoou Tichingitu, Tichingitu deve morrer.";
			link.l1 = "Não precisa ser pessimista. Sua prisão chegou ao fim. Eu ajudei a te libertar.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Piada de cara-pálida? Tichingitu está livre?";
			link.l1 = "Não, não estou brincando. Eles estão prestes a abrir sua cela e deixar você sair. Venha comigo, eu vou te tirar da prisão.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_2");
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "Aí está você, livre de novo. Vai lá, Tichingitu, tenta não roubar mais nada e não se meter em mais confusão! Melhor procurar uma aldeia indígena e viver com os seus, acho que eles não se importariam em te aceitar.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu não vai. Mestre salvou a vida de Tichingitu. Tichingitu fica. A vida de Tichingitu pertence ao mestre.";
			link.l1 = "Hã? Do que você está falando? Que mestre, que vida? Você não entende o que eu estou dizendo? Você está livre! Vai!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Índio tem dívida, mestre branco. Tichingitu serve você com lealdade e verdade. Tichingitu sabe lutar. Tichingitu morrerá em batalha pelo mestre. Ele fica.";
			link.l1 = "Meu Deus! Droga... Que tipo de senhor sou eu pra você, Tichingitu? Eu te ajudei, não pra te transformar em escravo.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu não é escravo. Tichingitu é um índio livre. Tichingitu quer servir você. Tichingitu sabe lutar, qualquer cachorro morre antes de chegar perto do mestre. Tichingitu sabe limpar e carregar mosquete. Tichingitu sabe atirar com mosquete.";
			link.l1 = "Embora... Sabe, Tichingitu, essa não é uma má ideia. Eu preciso de gente leal e você não parece ser um mau sujeito. Além disso, sabe atirar de mosquete. E o que vai fazer sozinho, afinal? Vai acabar roubando outra coisa e, da próxima vez, com certeza vai ser enforcado... Tudo bem, pode ficar. Mas lembre-se: a vida ao meu lado não vai ser tranquila.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "Tudo bem, chega. Vá em paz, irmão de pele vermelha. Que seus deuses cuidem de você!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_DlgExit_3");
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu não teme nada, mestre branco. Tichingitu tem prazer em servi-lo. Tichingitu será fiel até o último suspiro.";
			link.l1 = "Tudo certo. Bem-vindo à tripulação, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_Hire");
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu está ouvindo você, Capitão "+pchar.name+"!";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = ""+npchar.name+" vê confusão nos olhos do capitão "+pchar.name+".";
				Link.l1 = "Você, como sempre, enxerga direto na alma, meu amigo. Veja bem, preciso voltar para casa, para a Europa. Tomei uma decisão difícil – viajarei em outro navio, como passageiro.";
				Link.l1.go = "SharlieEpilog_Tichingitu_1";
				break;
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, estou prestes a partir para uma antiga aldeia indígena chamada Tayasal. Não vou mentir para você, é uma jornada extremamente perigosa e bem fora do comum: através de um ídolo de teletransporte. Você... Vai comigo?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, me faça um relatório completo sobre o navio.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Quero que você compre certos produtos toda vez que atracarmos.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Ouça minhas ordens!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nada no momento. Pode relaxar!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Relatório do navio? Tichingitu não tem relatório, mestre. Só arma e roupa. Tichingitu não pegou relatório de lugar nenhum.";
			Link.l1 = "Tanto faz, que seja.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Mestre, Tichingitu nunca entra numa colônia sem você. Quando Tichingitu entra numa loja – todo mundo acha que Tichingitu é ladrão de novo. Aí, cadeia.";
			link.l1 = "É, você provavelmente tem razão. Nada de prisão de novo. Além disso, ninguém nunca vai acreditar que você é um intendente.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Quais são as suas ordens?";
            Link.l1 = "Espere aqui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Me siga e não fique para trás!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Você precisa trocar o tipo de munição da sua arma de fogo.";
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
					Link.l5 = "Troque sua arma principal para o combate.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Quero que você mantenha distância do alvo.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Escolha o tipo de munição:";
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
			Dialog.Text = "No início da luta você usará:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Mosquete";
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
            dialog.Text = "Mudança de planos!";
            Link.l1 = "À vontade.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Mudança de planos!";
            Link.l1 = "À vontade.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Quão longe, Capitão? Diga a Tichingitu quantos jardas, mas não mais que vinte.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitão, perdoe Tichingitu, mas eu não entendo o que você diz.";
				link.l1 = "Desculpe, foi erro meu...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu fica parado, não se mexe. É isso que você quer, Capitão?";
				link.l1 = "Sim, exatamente isso.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu não consegue ficar a mais de vinte jardas do alvo. Aí ele erra.";
				link.l1 = "Está bem, mantenha distância de vinte jardas.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu entende tudo. Tichingitu vai assumir o cargo que você disser.";
			link.l1 = "Bom.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "A vida de Tichingitu, há muito tempo, se tornou a vida do meu Capitão. O índio não esquece o que o Capitão fez por Tichingitu. Tichingitu vai segui-lo para onde o Capitão mandar, sem perguntas, sem hesitação.";
			link.l1 = "Obrigado, meu amigo!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quando vamos partir?";
			link.l1 = "Um pouco mais tarde. Por enquanto, teremos que nos preparar para a viagem.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Pagamos cem dobrões ao homem branco, vamos embora e terminamos nosso trabalho em paz.";
			link.l1 = "E se a gente for pego de novo?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Pagamos mil dobrões.";
			link.l1 = "Cínico, mas muito perspicaz.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadalupe é pior.";
			link.l1 = "Como assim?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Lá, eles querem enforcar só o Tichingitu. Aqui, querem enforcar mais de um. Não é tão ruim assim.";
			link.l1 = "Agora isso é puro cinismo!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Tiro à queima-roupa. Capitão, o velho é forte, podemos salvá-lo se agirmos rápido.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "O homem branco não tem piedade. Muitos dos meus, Capitão. Tantos. Mas dos seus, ainda mais.";
			link.l1 = "Eles são do seu povo?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Algumas... algumas minhas.";
			link.l1 = "Aguente firme, amigo.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Mais 40 dobrões?";
			link.l1 = "Hã? Você está perguntando se eu vou pagar de novo pela libertação do Deluc da prisão?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Sim.";
			link.l1 = "Eu mesmo não tenho certeza... O que você acha?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Devemos tirá-lo da cadeia.";
			link.l1 = "Isso é honrado. Nunca abandone os seus, não é?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Ou deixe-o. Deixe os fracos para o jaguar na selva.";
			link.l1 = "Quem?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "O grande gato.";
			link.l1 = "Tichingitu, estou tendo dificuldade para te entender. Só me diga: o que devo fazer nessa situação?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Use a sua própria cabeça.";
			link.l1 = "Muito útil!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			ReturnOfficer_Tichingitu();
		break;
		
		// Эпилог
		case "SharlieEpilog_Tichingitu_1":
			dialog.text = "Capitão "+pchar.name+" não levar "+npchar.name+" com ele?";
			link.l1 = "Você é meu amigo, "+npchar.name+", e claro que o convido a fazer essa viagem comigo. Mas você precisa entender que, no Velho Mundo, as pessoas não estão acostumadas a ver índios. Vão apontar para você, achar que é meu escravo, e te tratar de acordo.";
			link.l1.go = "SharlieEpilog_Tichingitu_2";
		break;

		case "SharlieEpilog_Tichingitu_2":
			dialog.text = ""+npchar.name+" não se importar com isso. "+npchar.name+" saber que cara pálida desprezar índio, e seguir capitão "+pchar.name+", como prometer – até o último suspiro.";
			link.l1 = "Nem todos desprezam os índios. Mas a maioria encara com desconfiança – é a forma deles protegerem sua fé contra tudo que é estranho. De qualquer forma, não deixarei ninguém te humilhar ou te tomar por escravo. Tenho certeza de que ninguém da sua tribo jamais esteve na Europa – nem mesmo aquele xamã amaldiçoado nos sonhos mais ousados teria imaginado isso.";
			link.l1.go = "SharlieEpilog_Tichingitu_3";
		break;

		case "SharlieEpilog_Tichingitu_3":
			dialog.text = "Índio maskogue não ser marinheiro. Eles nunca chegar em Europa. Eu ouvir: grande canoa ir até lá por duas luas cheias.";
			link.l1 = "Sim, "+npchar.name+", e isso se o vento ajudar. Não se pode dizer que é um caminho fácil. Partiremos em duas semanas... e estou feliz que venha conosco. Para celebrar, quero organizar uma pequena festa na taverna. Sei que você não gosta da água de fogo, mas ainda assim, ficarei feliz se se juntar a nós.";
			link.l1.go = "SharlieEpilog_Tichingitu_4";
		break;
		
		case "SharlieEpilog_Tichingitu_4":
			dialog.text = ""+npchar.name+" vir. Mas talvez melhor ataque de festa?";
			link.l1 = "Ha-ha. Dessa vez não, meu amigo, não é ocasião para isso. Avisarei quando começarmos. Agora preciso ir – há assuntos a tratar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tichingitu = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
