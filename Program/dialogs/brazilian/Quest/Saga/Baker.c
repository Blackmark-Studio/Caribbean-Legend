// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
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
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Não, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Obrigada, capitão! Nem consigo imaginar o que teria feito sem você...";
			link.l1 = "Consigo imaginar. Você teria morrido de fome ou acabado na barriga de algum selvagem da Dominica. Mas agora tem a chance de me pagar de volta.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Como posso ajudar você, Capitão?";
			link.l1 = "Quero saber mais sobre um homem. Ele é nosso conhecido em comum, por assim dizer. Na verdade, um amigo muito próximo seu. Refiro-me ao Capitão Butcher. Sim, aquele que você enforcou há vinte anos. Meu Deus, por que ficou tão pálido? Aceita um gole de rum?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Você... você foi enviado por ele?";
			link.l1 = "Que absurdo! Como eu poderia ter sido 'enviado por ele' se ele está morto? Estou mais interessado nas coisas que ele deixou para trás do que no próprio Carniceiro. Cartas, documentos, coisas desse tipo. Talvez você tenha encontrado algo nos bolsos dele... Espere! Não entendo. Você realmente acha que o Carniceiro está vivo? Foi você mesmo quem o executou!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Merda! Você não faz ideia. Isso significa que você não foi enviado pelo Açougueiro como eu pensei...";
			link.l1 = "Bem, bem. Isso está ficando cada vez mais interessante. Parece que Henry tinha todos os motivos para temer o Açougueiro, e é por isso que morreu de ataque cardíaco... O Açougueiro está vivo?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "Ele está, Capitão... E eles estão me procurando.";
			link.l1 = "Raymond, me disseram que você não é tolo. Não tente bancar o esperto comigo. Aqui você está a salvo de qualquer ameaça. Conte tudo o que sabe e vou pensar em uma forma de te ajudar. Talvez tenhamos inimigos em comum. Vamos começar pelo Açougueiro.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "Ele está vivo, mas agora usa outro nome! Os homens dele vieram me procurar na noite da execução. Jackman e outro sujeito com um apelido estranho. Se não me engano, era 'O Afogado'.";
			link.l1 = "Carrasco. Henrique, o Carrasco.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Right! They offered me a simple deal – die in the most painful way, or save their captain. So I had to fake the execution with some special equipment I had made in my spare time. You see, such an arrangement of belts and clamps can distribute the body's weight.\nAll I had to do was attach it to a secret hook in the noose. The 'corpse' had to play his part well, though. I must say, Lawrence's acting was most convincing; he did everything right, except he refused to piss himself, because of...";
			link.l1 = "Você acabou de chamar o Açougueiro de 'Lawrence'?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "Esse é o verdadeiro nome dele. Eu te disse que ele se chama Lawrence Beltrope. Estou inquieto desde que ele voltou ao Caribe há um ano. E quando descobri que algumas pessoas perigosas estão me procurando...\nCheguei até a escrever uma confissão para as autoridades, só por precaução. Carrego comigo o tempo todo, pois tenho medo demais de entregar. Podem achar que fui cúmplice de propósito. Por favor, me deixe ficar com sua tripulação. Juro, sou um excelente médico e posso ser de grande ajuda para você.";
			link.l1 = "Certo. E quanto aos pertences pessoais do Açougueiro... digo, do Beltrope? Ele é parente do Thomas Beltrope?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "No clue. I don't have anything special left from Beltrope himself. But I will give you everything I have; you are free to do whatever you want with it. All papers related to the subject are in my bag. I saved everything just in case and keep it close to me.\nHere, take a look... this is the legend of Captain Butcher, this is my confession... These are things that belonged to Joshua Leadbeater...";
			link.l1 = "Pare! Leadbeater? Quem é esse?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Oh! Ele era um homem muito especial. Foi ele quem caçou o Açougueiro em pessoa. As pessoas se lembravam dele como o 'homem mascarado'. Ele foi assassinado logo após a execução do Açougueiro. Alguém cortou sua garganta com um dente de tubarão! Um golpe e tudo acabou. Enquanto ainda estava vivo, deve ter sofrido horrores.\nSe você tivesse visto o rosto dele sob a máscara, era só carne viva! Ele tinha essa página de diário no bolso quando morreu. Deve ser dos escritos de Jessica Rose. História arrepiante! Leia, vai deixar tudo bem mais claro.\nE este é o próprio dente. Consegue ver as letras? S.D.... Seja lá o que isso signifique. Ainda tem umas manchas de sangue.";
			link.l1 = "Chega! Preciso ler tudo com atenção e pensar direito. E você vai ser meu passageiro ou médico de bordo até eu resolver tudo isso. Pode ficar tranquilo, Raymond, você está seguro no meu navio.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Sim, capitão?";
			Link.l1 = "Ouça minhas ordens!";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Capitão, vejo que está um tanto preocupado. E seu rosto está meio pálido... Em outras circunstâncias, eu lhe ofereceria um dos meus tônicos, mas...";
				Link.l1 = "Vejo que você aprendeu um pouco de medicina, "+npchar.name+". Obrigado, estou bem. Só estou prestes a dar um passo que talvez não ousasse em outras circunstâncias.";
				Link.l1.go = "SharlieEpilog_Baker_1";
				break;
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, me dê um relatório completo sobre o navio.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Quero que você compre certos produtos toda vez que atracarmos.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "Não é nada. Dispensado!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Vamos lá, capitão, sou médico, não intendente. Embora, no passado, eu já tenha trabalhado de outra forma... deixa pra lá. Realmente não entendo de contabilidade, desculpe.";
			Link.l1 = "Certo, que seja. Você é meu médico - como combinamos depois que entrou para minha tripulação.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Capitão, sendo bem sincero, nunca tive muita experiência com comércio. Nunca negociei, nunca acompanhei preços. E... prefiro ficar no navio, se não se importar. Alguns desses mercadores podem me reconhecer e, antes que perceba, homens mascarados vão aparecer por aqui.";
			link.l1 = "Então, você vai continuar vivendo com medo do seu passado... Certo, respira fundo, eu mesmo faço isso.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Ordens?";
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
					Link.l3 = "Mude o tipo de munição da sua arma de fogo.";
					Link.l3.go = "SetGunBullets";
				}	
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Houve uma mudança de ânimo!";
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
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// Эпилог
		case "SharlieEpilog_Baker_1":
			dialog.text = "Hm... Parece que estou deixando passar algo. Achei que as notícias que viriam o deixariam animado.";
			link.l1 = "Do que está falando?";
			link.l1.go = "SharlieEpilog_Baker_2";
		break;

		case "SharlieEpilog_Baker_2":
			dialog.text = "Cof... Desculpe. Nem sei o que me deu. Talvez tenha sido o sol forte demais. Na verdade, queria falar com você, capitão.";
			link.l1 = "É mesmo? E sobre o quê?";
			link.l1.go = "SharlieEpilog_Baker_3";
		break;
		
		case "SharlieEpilog_Baker_3":
			dialog.text = "Já estou velho demais para essas batalhas navais sem fim, mesmo participando apenas indiretamente. Tenho algumas economias e gostaria de ir para terra firme. Montar um consultório particular. Espero que não se oponha.";
			link.l1 = "Claro que não, "+npchar.name+". Com certeza vou sentir falta de um oficial tão competente quanto você. Mas entendo e respeito sua decisão. Boa sorte. Tenho certeza de que logo será um médico famoso e respeitado.";
			link.l1.go = "SharlieEpilog_Baker_nothing";
			link.l2 = "Está tomando uma decisão sábia, e claro que não me oponho. Vou providenciar para que receba um salário mensal extra — nunca é demais. Bem... só posso desejar sorte na nova vida.";
			link.l2.go = "SharlieEpilog_Baker_salary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // только если есть жена
			{
				link.l3 = "Ha-ha, é claro que não vou me opor, querido "+npchar.name+". Na verdade, neste momento eu o entendo como ninguém. Aqui, pegue. São três salários mensais. Espero que tudo dê certo para você.";
				link.l3.go = "SharlieEpilog_Baker_salary_X3";
			}
		break;
		
		case "SharlieEpilog_Baker_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "SharlieEpilog_Baker_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Baker_salary_X3":
			dialog.text = "Obrigado, capitão. Acho que você também deveria procurar uma casa aconchegante para morar com sua esposa o quanto antes. Afinal, o balanço do mar não faz muito bem a certos processos no ventre...";
			link.l1 = "No ventre? Não entendi... Ninguém está enjoado no nosso navio.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_2";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Baker_salary_X3_2":
			dialog.text = "Só estava pensando alto, capitão, não ligue. Cuide bem da sua esposa e de si mesmo.";
			link.l1 = "E você também se cuide, "+npchar.name+". Quando se estabelecer, me mande notícias pelo abade Benoît. Você o encontrará na igreja de Saint-Pierre.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_3";
		break;
		
		case "SharlieEpilog_Baker_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
