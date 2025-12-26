#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Olha, senhor, não quer comprar uma coisinha divertida? É baratinho, só uns poucos milhares de pesos...";
				link.l1 = "Hum. Provavelmente roubou essa 'coisinha', e agora está tentando se livrar dela?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Olá. Meu nome é "+GetFullName(npchar)+". Imagino que você não está feliz em me conhecer, mas talvez pelo menos lembre do meu nome...","Saudações, "+GetAddress_Form(NPChar)+". Meu nome é "+GetFullName(npchar)+".","Meu nome é "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+". Prazer em te conhecer.");
				link.l1 = RandPhraseSimple("Saudações.","Olá.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Ei, escuta, você gostaria de ganhar alguns milhares de pesos em vez dessas esmolas patéticas?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Aquele pingente com um camafeu... Onde você o encontrou?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Veja até onde eu cheguei...","Viver de esmolas não é fácil...","Eu daria qualquer coisa para sair dessa pobreza!","Você de novo?..","block",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Entendi. Bem, não é nada demais.","Claro. Bem, você sabe, o maior homem da história foi o mais pobre.","Então você devia começar a fazer alguma coisa, não ficar sentado aqui o dia todo.","Ah-ha. Já estou te irritando?",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("O que você precisa?","O que você quer?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "Ei, escuta, você gostaria de ganhar alguns milhares de pesos em vez dessas esmolas patéticas?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Aquele pingente com pedras preciosas... Onde você o encontrou?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("Pode me contar algo interessante?","O que há de novo na cidade?","Ah, eu gostaria de ouvir as últimas fofocas...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Não, por quê, já está irritado? Não estou exatamente ocupado, como pode ver...","Só me cansa. Apesar de pobre, ainda sou um homem.");
			link.l1 = "Heh, entendi...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, "+GetAddress_Form(NPChar)+", dizem muitas coisas terríveis sobre você. Mas eu continuo acreditando nas pessoas – até mesmo em gente como você. Por favor, me dê uma esmola para pão e água, tenha piedade de mim.","Eu te imploro, "+GetAddress_Form(NPChar)+"! Por favor, não vire as costas para um pobre, dê uma esmola para uma refeição...");
				link.l1 = RandPhraseSimple("Não vou te dar nada.","Você vai se virar sem dinheiro.");
				link.l1.go = "exit";
				Link.l2 = "Certo, e de quanto você precisa?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("De você? Nada.","Não preciso de nada, "+GetAddress_Form(NPChar)+", obrigado.");
				link.l1 = RandPhraseSimple("Hum, tudo bem.","Aparentemente, sua vida nem é tão ruim assim, camarada.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "Eu não recusaria nem mesmo uma moedinha de cobre, "+GetAddress_Form(NPChar)+". Tanto quanto sua bolsa e sua misericórdia puderem oferecer...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Zombar dos fracos e cansados é um pecado...";
				link.l1 = "Ha-ha-ha! Você realmente achou que eu ia te dar dinheiro, seu mendigo maluco?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Obrigado por "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+". Agora posso comprar um pouco de pão com esse dinheiro...";
				link.l1 = "Aqui, vagabundo - vai se fortalecer um pouco.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Obrigado, "+GetAddress_Form(NPChar)+". Com esse dinheiro, eu vivo uma semana!";
				link.l1 = "Foi um prazer ajudar.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Obrigado, "+GetAddress_Form(NPChar)+". Vou contar a todos sobre a sua bondade!";
				link.l1 = "Isso não é realmente necessário.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Obrigado, respeitado "+GetSexPhrase("senhor","senhora")+" "+GetAddress_Form(NPChar)+". Que o Senhor cuide de você...";
				link.l1 = "É, a proteção Dele com certeza não faria mal!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Obrigado, "+GetSexPhrase("meu estimado senhor","minha estimada senhora")+" "+GetAddress_Form(NPChar)+". Desejo tudo de bom para você!";
				link.l1 = "Obrigado, camarada.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "Escute, "+GetAddress_Form(NPChar)+", você ficou maluco ou o quê? Você está me dando "+FindRussianMoneyString(iTemp)+"! Eu não posso aceitar esse dinheiro, com certeza tem alguma pegadinha... Me deixe em paz!";
				link.l1 = "Bem, como quiser...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "Vinte e cinco mil aceitos ... Esse dinheiro vai ser suficiente para mim e para a Lelya por um ano inteiro!";
				link.l1 = "Sobreviva a este ano primeiro...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "Escute, "+GetAddress_Form(NPChar)+", você ficou maluco ou o quê? Você está me dando "+FindRussianMoneyString(iTemp)+"! Eu não posso aceitar esse dinheiro, com certeza tem alguma pegadinha... Me deixe em paz!";
				link.l1 = "Bem, como quiser...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Que pergunta boba, señor! Claro que eu aceitaria! Mas... o que vou ter que fazer? Você não vai me dar esse dinheiro só pelo meu sorriso bonito, né.";
			link.l1 = "Claro que não. Escute bem. Estou agindo em nome do próprio governador. Sua Graça desconfia que alguém no estaleiro está sabotando de propósito o lançamento do 'Alacantara', o galeão dele. E as suspeitas só aumentaram depois que um espião francês foi capturado recentemente...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Sua Graça já ouviu as desculpas do mestre de doca, mas não tem certeza se ele falou a verdade. Precisamos descobrir quem está sabotando o trabalho e por quê. Vá até o cais, dê uma olhada e pergunte aos trabalhadores por que diabos o 'Alacantara' ainda não está pronto para zarpar...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Ninguém vai suspeitar de você, talvez até consiga pegar um monte de tabaco. Quanto a mim, ninguém vai me contar nada. Todo mundo vai saber para quem estou trabalhando. Se conseguir descobrir algo que preste, vai receber três mil pesos. Dá pra largar esse seu 'trabalho' por pelo menos um mês.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Três mil pesos? Mas, estimado senhor...";
			link.l1 = "Está querendo negociar comigo ou o quê? Ah, e se descobrir quem está por trás dessa enrolação toda, ganha mais dois mil. Fechado?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Certo, señor. Não deve ser muito difícil – muitos dos meus velhos camaradas trabalham nos cais hoje em dia. Olha, eu também já fui marinheiro, faz tempo. Uns dez anos atrás...";
			link.l1 = "Depois você poderá me contar a sua história de vida. Encontre-me no cais à noite, depois das onze. Agora vá.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			DialogExit();
			AddDialogExitQuestFunction("Trial_Poorman_DlgExit");
		break;
		
		case "trial_6":
			dialog.text = "Boa noite, señor...";
			link.l1 = "E aí? Descobriu alguma coisa?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "Eu trouxe, señor, eu trouxe. Não sei se tudo bate com o que você me contou... Trouxe o dinheiro? Cinco mil pesos.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Não se preocupe. Aqui está seu dinheiro. Agora, desembucha.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Primeiro a informação, depois o dinheiro. Vamos, não perca meu tempo!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Você está tentando me enganar, señor! Se não vai pagar - vá pedir para outra pessoa você mesmo. E nem pense em sacar a espada ou vou chamar os guardas!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Trial_FailPoormanInPort");
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Então é assim que está a situação: o 'Alcantara' já está pronto para zarpar faz tempo, mas não foi carregado de propósito, por ordem do próprio governador. Bom, foi isso que me disseram. Agora os carpinteiros estão fazendo todo tipo de serviço pequeno, nada que impeça o navio de partir. Todo mundo está esperando a chegada de uma barca de Cartagena. O problema é que, na opinião do capitão, o 'Alcantara' não tem pólvora suficiente a bordo. Por isso, o navio está aqui há dias, esperando a 'Puebla' trazer a pólvora. Mas todo mundo acha que essa espera é pura perda de tempo, então, se a 'Puebla' não chegar em três dias, o 'Alcantara' vai levantar âncora sem a pólvora...";
			link.l1 = "É mesmo? E quem te contou isso? Nome?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Um dos marinheiros do 'Alcantara' — Felipe Dabinho... Mas isso na verdade não é segredo nenhum, e Sua Graça, o próprio governador, tinha ordenado...";
			link.l1 = "Entendi. Era o que eu imaginava. Espiões franceses estão na cidade, mas esses idiotas falam demais, parecem feirantes, inacreditável! Qualquer recém-chegado pode descobrir tudo o que quiser sobre os planos de Sua Graça. Ah, esse Felipe Dabinho está encrencado até o pescoço agora! E o contramestre do 'Alacantara' também! É culpa dele que a tripulação não saiba nada de disciplina!";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Oh... Então, você sabia desde o começo? Mas por quê... Não é minha culpa! Foi você quem mandou eu fazer isso!";
			link.l1 = "Não foi sua culpa, você não precisa se preocupar com isso, ninguém vai te punir. Agora sabemos que a tripulação do 'Alacantara' pode fofocar qualquer informação para o inimigo – até mesmo o que deveria ser mantido em segredo. Certo, pode ir agora. Obrigado pela sua ajuda. Vai gastar seu dinheiro.";
			link.l1.go = "trial_11";
			link.l2 = "Adeus. (Mate ele)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddDialogExitQuestFunction("Trial_KillPoormanInPort");
		break;
		
		case "trial_11":
			DialogExit();
			AddDialogExitQuestFunction("Trial_PeacePoormanInPort");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Com licença, senhor... Ganhei isso num jogo de dados contra um estranho. Achei que fosse um amuleto de cura encantado, mas me enganei... Não cura doença nenhuma, e os comerciantes do mercado não querem saber disso. E aí está você – um marinheiro, um capitão, um homem instruído. Dê uma olhada, talvez ache útil.\nPara você, esses poucos milhares não são nada, mas pra mim é pão e um gole de rum por um mês. Olhe, senhor...";
			link.l1 = "Certo, mostre...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Aqui...";
			link.l1 = "Mais ou menos... É uma coisa interessante, concordo. Tenho certeza de que foi roubada das aldeias indígenas. Tudo bem, eu fico com ela. Aqui está o seu dinheiro.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Obrigado, senhor! Espero que isso lhe traga sorte! Que o Senhor o proteja!";
			link.l1 = "Boa sorte, camarada. Não gaste todo o dinheiro de uma vez na taverna.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Eh, "+GetAddress_Form(NPChar)+", por que você se importa com uma bugiganga velha?";
			link.l1 = "Quando eu chutar essa sua cabeça idiota com a minha bota, você vai entender na hora por que eu me importo.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Esse pingente pertencia à Betsy Price. Então, onde você o encontrou?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "Estava deitado perto da casa com a lanterna, "+GetAddress_Form(NPChar)+". Pisoteado na lama pela bota de um homem bruto. Mas ninguém mora naquela casa há muito tempo, então decidi que estava sem dono...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "Estava deitado perto da casa com a lanterna, "+GetAddress_Form(NPChar)+". Pisoteada na lama pela bota de um brutamontes. Mas ninguém mora naquela casa há muito tempo, então achei que estava abandonada...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
