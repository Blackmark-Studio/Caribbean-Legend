// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Não quero conversar com você. Você ataca moradores pacíficos sem motivo e ainda provoca briga. Cai fora, ateu!";
				link.l1 = "Como quiser...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Não me surpreende que você tenha sobrevivido. Misteriosos são os caminhos do Senhor. A vida e a morte estão em Suas mãos.";
				link.l1 = "Concordo plenamente com você, Irmão Julian.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bem-vindo à sagrada igreja da nossa ilha, meu filho. As portas estão sempre abertas para você. Sou o Irmão Julian, e fico feliz em receber qualquer servo do nosso grande Senhor.";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Prazer em conhecê-lo, Irmão Julian.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Posso comprar algumas poções de você?";
				link.l2.go = "potion";
				link.l3 = "Você tem algum objeto sagrado à venda?";
				link.l3.go = "amulet";
				link.l5 = "Só queria rezar aqui e saber como você está. Até mais!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "I hope that you will visit our church more often. Take care of your soul, my child. I am also able to heal your body; I work here not only as a pastor, but also as a doctor.";
			link.l1 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Posso comprar algumas poções com você?";
			link.l2.go = "potion";
			link.l3 = "Você tem algum item sagrado à venda?";
			link.l3.go = "amulet";
			link.l4 = "Preciso ir, irmão Julian. Até mais!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Claro, meu filho. De qual poção você precisa?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Uma poção de cura simples.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Um elixir de cura.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Um antídoto.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Uma mistura de ervas.";
				link.l4.go = "potion4";
			}
			link.l5 = "Me desculpe, Irmão Julian, mudei de ideia.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Uma poção? 90 pesos, meu filho.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Pegue-os, Irmão Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Agora não tenho moedas suficientes... Volto mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Um elixir? 500 pesos, meu filho.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Pegue-os, Irmão Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Agora não tenho moedas suficientes... Volto mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Um antídoto? 200 pesos, meu filho.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Pegue-os, Irmão Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Agora não tenho moedas suficientes... Volto mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Uma mistura? 900 pesos, meu filho.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Pegue-os, Irmão Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Agora não tenho moedas suficientes... Volto mais tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Aqui. Tome seu remédio. Que Deus te guie!";
			link.l1 = "Obrigado, Irmão Julian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Sim, posso te dar alguns amuletos sagrados que protegem as pessoas de ferimentos e doenças. O preço é o mesmo para qualquer amuleto – dez dobrões de ouro. Posso te oferecer "+XI_ConvertString(npchar.quest.amulet)+" hoje.";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "Sim, eu quero comprar este amuleto. Aqui está o seu ouro.";
					link.l1.go = "amulet_pay";
					link.l2 = "Eu não preciso desse amuleto, Irmão Julian. Vou esperar até você conseguir o que eu preciso.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "Agora não tenho moedas suficientes... Volto mais tarde.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Não, meu filho, infelizmente não tenho mais nada. Venha me ver outro dia, talvez eu encontre algo para você.";
				link.l1 = "Fechado, Irmão Julian.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Obrigado, meu filho. Seu dinheiro será bem usado. Pegue seu amuleto e que Deus te abençoe!";
			link.l1 = "Obrigado, Irmão Julian.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estou ouvindo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui, Irmão Julian?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Quantas pessoas vivem na sua paróquia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Quem vende mercadorias aqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Existe algum risco de destruição para a ilha? Tempestades, talvez?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Me desculpe...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Assim como muitos dos moradores daqui, meu filho. Meu navio afundou numa tempestade durante a viagem de Havana para a Nova Espanha. Graças a Deus, sobrevivi e agora sirvo a Ele aqui, ajudando almas perdidas a encontrar seu verdadeiro caminho.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Menos do que eu gostaria. A maioria dos Narvais prefere a violência à misericórdia, e os Rivados são pobres almas perdidas. Eles seguem cegamente seus rituais pagãos, colocando suas almas imortais em risco. Há um feiticeiro perigoso entre eles, e ele precisa ser purificado pela Santa Inquisição.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero owns a tavern on the Fleron, where you can find food, drinks, and a warm bed. Axel Yost sells a wide variety of goods on the 'Esmeralda'. Ask people on the streets, my son; many of them find interesting things in the outer ring.";
			link.l1 = "Obrigado!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Está tudo nas mãos do nosso Senhor, meu filho. Nós acreditamos Nele e confiamos Nele. Grandes problemas sempre passaram longe da nossa ilha — as tempestades costumam acontecer lá fora, mas aqui sempre reina a tranquilidade.";
			link.l1 = "Obrigado. Você me tranquilizou.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você está fazendo aí, hein? Ladrão!","Olha só isso! No instante em que me perdi em pensamentos, você resolveu fuçar nos meus baús!","Resolveu fuçar nos meus baús? Não vai sair impune!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Veio fuçar nos meus baús? Não vai sair impune!";
			link.l1 = "Garota tola!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Olha, é melhor você guardar sua arma. Isso me deixa nervoso.","Sabe, andar por aí com uma lâmina não é permitido aqui. Guarde isso.","Escuta, não fique bancando um cavaleiro medieval correndo por aí com uma espada. Guarda isso, não combina com você...");
			link.l1 = LinkRandPhrase("Certo.","Certo.","Como você diz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ouça, eu sou um cidadão desta cidade e gostaria que você guardasse sua espada.","Escute, sou um cidadão desta cidade e peço que guarde sua espada.");
				link.l1 = LinkRandPhrase("Tudo bem.","Certo.","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, amigo, andando por aí com uma arma. Isso me deixa nervoso...","Não gosto quando as pessoas passam na minha frente com as armas em punho. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
