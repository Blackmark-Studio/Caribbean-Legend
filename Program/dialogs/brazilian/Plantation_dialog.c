// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Precisa de alguma coisa?";
			link.l1 = "Não, não quero.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Estou tão cansado, já estou quase caindo...","Não posso continuar vivendo assim!"),RandPhraseSimple("Esse trabalho está me matando.","Os guardas querem todos nós mortos!"));				
			link.l1 = RandPhraseSimple("Que pena.","Me desculpe.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Escuta, vai embora!","Cai fora!"),RandPhraseSimple("O que você quer?!","Cai fora daqui, agora!"));				
			link.l1 = RandPhraseSimple("Hm...","Bem...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Vá incomodar o chefe da plantação","Não distraia os escravos, camarada."),RandPhraseSimple("Meu trabalho é motivar esses bastardos preguiçosos.","Aff, quente demais hoje, como sempre..."));
			link.l1 = RandPhraseSimple("Entendi...","De fato...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Pirata?! Peguem ele!","Ele é um pirata! Ataquem!");
					link.l1 = RandPhraseSimple("Pirata. E daí?","Heh, vai em frente e tenta.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Ho-ho, você está navegando sob a bandeira de "+NationNameGenitive(sti(pchar.nation))+"! Acho que nosso comandante vai ficar feliz em falar com você!","Ora, ora, está cheirando a "+NationNameAblative(sti(pchar.nation))+" aqui! Um espião?! Está na hora de você falar com o nosso comandante.");
				link.l1 = RandPhraseSimple("Primeiro, vou te mandar para o inferno!","Chegou a hora de você conversar com a minha lâmina!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Pirata?! Peguem ele!","Ele é um pirata! Ataquem!");
						link.l1 = RandPhraseSimple("Pirata!? Onde?","Heh, vai em frente e tenta.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Quem é você e o que quer aqui?","Pare! O que você está fazendo aqui?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Quero falar com o responsável deste lugar para tratar de negócios. Tenho uma licença de comércio.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Quero falar com o responsável deste lugar para tratar de negócios.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Confiável) Nobres senhores, estou aqui para um comércio justo e vantajoso para ambos. Por favor, deixem-me falar com o dono da plantação.";
						link.l2.go = "mtraxx_soldier_1";
						Notification_Perk(true, "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Quem é você e o que quer aqui?","Pare! O que você está fazendo aqui?");
					link.l1 = "Quero falar com o responsável daqui para tratar de negócios.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "Uma licença? Espere um segundo... Ha-ha, isso é engraçado! Eu sei quem você é. Você está sendo procurado, camarada! E a recompensa pela sua cabeça é enorme! Peguem ele!";
				link.l1 = RandPhraseSimple("Bom, nesse caso você vai ter que encarar minha lâmina!","Vai se ferrar.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "Vamos ver... ha! Sua licença expirou. Então venha comigo, vou levá-lo até o comandante...";
				link.l1 = RandPhraseSimple("Merda! Acho que chegou a hora de você conhecer minha lâmina, camarada.","Acho que não...");
				link.l1.go = "fight";	
				break;
			}
			dialog.text = "Tudo bem. Pode entrar. Comporte-se e não incomode os escravos.";
			link.l1 = "Não se preocupe, amigo.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "Negócios? Ha-ha! Ora, isso é engraçado! Você cheira a "+NationNameAblative(sti(GetBaseHeroNation()))+" de mil léguas! Está na hora de você conhecer nosso comandante.";
			link.l1 = "Não, acho que está na hora de você conhecer minha lâmina.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Tudo bem. Pode entrar. Comporte-se e não incomode os escravos.";
			link.l1 = "Não se preocupe, amigo.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Ande, siga em frente!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "Qual é o seu negócio aqui, señor?";
				link.l1 = TimeGreeting()+", señor. Tenho uma proposta de negócio para você. Tenho escravos para vender. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+". Interessado?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "Qual é o seu negócio aqui, señor?";
			link.l1 = "Só estou dando uma volta, queria dizer oi.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Você de novo, señor. Como vai?";
				link.l1 = "I have a business proposal for you. You produce sugar and cacao. I'd like to purchase your goods, but not with money; I can offer my own goods in exchange. Perhaps we could strike a bargain?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "Você de novo, señor. Como vai?";
				link.l1 = "I have a business proposal for you. You produce sugar and cacao. I'd like to purchase your goods, but not with money; I can offer my own goods in exchange. Perhaps we could strike a bargain?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Você de novo, señor. Como vai?";
			link.l1 = "Obrigado, estou bem.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Tenho que decepcioná-lo, señor, mas não precisamos de escravos neste momento. O capitão Eduardo de Losada já nos forneceu piratas que capturou em sua última incursão.";
			link.l1 = "Piratas aqui? Como você consegue dormir aqui?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ah, vejamos então... Vou comprar seus escravos. Só me parece que você não é quem diz ser. Venha comigo até o gabinete do comandante, minha cara, e se eu estiver enganado, vou compensá-la totalmente pelo transtorno. E agora, peço desculpas. Guarda!";
				link.l1 = RandPhraseSimple("Pode sonhar, não vou me deixar capturar vivo!”, “Só por cima do meu cadáver!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Temos uma boa guarda, então as chances de uma rebelião são baixas. Mas você está certo em uma coisa: esses desgraçados são péssimos trabalhadores. Eu não teria comprado eles se o governador não tivesse me pedido para mostrar respeito ao don de Losada. Além disso, ele também não pediu muito por eles.";
			link.l1 = "Entendo. Então terei que navegar até Los-Teques... Señor, posso dar uma volta pela sua plantação e explorá-la? Talvez eu queira comprar alguns dos seus produtos...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Você é comerciante?";
			link.l1 = "De certa forma, sim. Não sou um comerciante profissional, mas jamais deixaria passar um bom negócio.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Interessante. Muito bem, você tem minha permissão. Volte se tiver alguma ideia.";
			link.l1 = "Obrigado, señor. Acho que vou aceitar.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Por que não? Que mercadorias você está oferecendo?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 caixas de café.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 caixas de baunilha.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 caixas de copra.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Quinhentas caixas de café? Muito bem... Vamos ver... (contando) Estou pronto para trocar seu café por "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacos de açúcar e "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  caixas de cacau. Fechado?";
			link.l1 = "Hum... Eu esperava condições melhores. Mas, tanto faz. Fechado!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Confiável) Estimado senhor, permita-me discordar! Trouxe mercadorias da mais alta qualidade. Conheço o valor de cada unidade, tanto do que ofereço quanto do que o senhor oferece em troca. Eu mereço uma parte um pouco maior da sua parte, e esse acordo ainda será lucrativo para você – disso o senhor sabe muito bem.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Quinhentas caixas de baunilha? Muito bem... Vamos ver... (contando) Estou pronto para trocar sua baunilha por "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacos de açúcar e "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  caixas de cacau. Negócio?";
			link.l1 = "Hum... Eu esperava condições melhores. Mas, tanto faz. Fechado!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Confiável) Estimado senhor, permita-me discordar! Trouxe mercadorias da mais alta qualidade. Conheço o valor de cada unidade, tanto do que ofereço quanto do que recebo em troca. Acho que mereço uma parte um pouco maior da sua parte, e esse negócio ainda será lucrativo para você – disso o senhor sabe muito bem.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Quinhentas caixas de copra? Muito bem... Vamos ver... (contando) Estou pronto para trocar sua copra por "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacos de açúcar e "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  caixas de cacau. Fechado?";
			link.l1 = "Hum... Eu esperava condições melhores... Mas quer saber? Fechado!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Confiável) Estimado senhor, permita-me discordar! Trouxe mercadorias da mais alta qualidade. Conheço o valor de cada unidade, tanto do que ofereço quanto do que o senhor oferece em troca. Acho que mereço uma parte um pouco maior da sua parte, e esse negócio ainda será lucrativo para você – o senhor sabe disso muito bem.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Excelente! É um negócio lucrativo para nós dois! Quando faremos a troca?";
			link.l1 = "Eu preciso preparar as mercadorias primeiro. Você também, acredito eu. Vamos começar a troca amanhã às quatro da tarde. Meus homens vão entregar as caixas antes do pôr do sol.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Fechado. Então, até amanhã, señor!";
			link.l1 = "Até mais...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "É isso, señor. Se algum dia precisar de açúcar ou cacau, venha me procurar. Sempre que quiser!";
			link.l1 = "Se este acordo for lucrativo, nos veremos de novo. Agora devo ir, señor.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Adeus, senhor!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Você não parece um comerciante, estrangeiro. Mostre sua licença.";
			link.l1 = "Tenha dó! Um pedaço de papel agora decide quem pode negociar ou não? Essas licenças são caras demais! Comecei a negociar faz pouco tempo, mas já virou minha paixão! Me deixa passar, e prometo falar bem de vocês dois para o dono.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Você tem lábia, seu pão-duro. Tá bom, vai lá. Mas não esquece de avisar o chefe que fomos nós que te indicamos pra ele.";
			link.l1 = "Com certeza. Obrigado.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "Você entende bem dos preços atuais, Capitão! Dá pra ver que você tem jeito pra negociação, mesmo parecendo um novato. Muito bem, se suas mercadorias forem mesmo de primeira, acho que posso acrescentar um extra pra você.";
			link.l1 = "Claro, de primeira classe, eu juro! Mais uma coisa, senhor. Gostaria de comprar algo de você.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "Oh? E o que seria isso?";
			link.l1 = "Alguém, não alguma coisa. Gostaria de comprar um dos seus escravos como criado pessoal. Isso é possível?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Sem problema. Vamos encontrar alguém adequado para você.";
			link.l1 = "Estou interessado em um escravo em especial. Aquele de rosto encantador—alguém de quem você não teria vergonha de levar a eventos formais ou servir vinho aos seus convidados. Ele se apresentou como Jean Picard. Já simpatizamos um com o outro.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Sim, há interesse por Jean Picard – e não só para servir vinho. Um inglês influente já entrou em contato comigo. Um homem chamado, como era mesmo... Pattornson? Ele me entregou uma carta.";
				link.l1 = "Mas nem Pattornson nem o cliente dele apareceram ainda. Estou pronto para comprar o Jean de você aqui e agora. Diga seu preço – as damas estão esperando!";
				link.l1.go = "mtraxx_PlantVykup_10";
				Notification_Skill(true, 70, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ah, entendi, vocês se deram bem. Mas receio que preciso recusar – Jean Picard não está à venda. Sinto muito, señor.";
				link.l1 = "Oh? Por quê? Estou disposto a pagar muito bem. É só dizer o seu preço.";
				link.l1.go = "mtraxx_PlantVykup_6";
				Notification_Skill(false, 70, SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Inestimável. Ele já tem um comprador. Eu já o prometi para outra pessoa. Não há mais o que dizer. Vamos voltar ao nosso acordo inicial e concluir a troca.";
			link.l1 = "Hum, como quiser, señor.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Excelente! É um negócio lucrativo para nós dois! Quando vamos fazer a troca?";
			link.l1 = "Eu preciso preparar as mercadorias primeiro. Você também, acredito eu. Vamos começar a troca amanhã às quatro da tarde. Meus homens vão entregar as caixas antes do pôr do sol.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Combinado. Então, até amanhã, señor!";
			link.l1 = "Até mais...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Como quiser, señor. Mas saiba que o preço é alto: quinhentos dobrões.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Isso não é problema – aqui está. Um bom criado pessoal vale mais do que um escravo comum, como você bem sabe.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "Que preço alto você colocou, senhor. Mas estou muito interessado nesse escravo. Espere aqui. Se o Pattornson aparecer, diga que o Picard já foi vendido – ha-ha-ha!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Você tem razão. Vou providenciar tudo. Picard vai estar te esperando lá fora.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Se ele vier com o valor completo, duvido que eu vá recusá-lo. Então se apresse, Capitão.";
			link.l1 = "Volto já.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Você trouxe o ouro para Jean Picard, Capitão? O tempo está passando.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Estou bem ciente disso. Então, aqui está o seu ouro, e me entregue meu novo criado.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Ainda estou juntando - foi você quem colocou um preço tão alto, señor.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Eu nunca vi ninguém gastar tanto para adquirir um criado. Mas, pelo jeito que você está vestido, deve estar acostumado a compras tão extravagantes. Vou avisar meus homens, e Picard estará esperando por você na saída.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
