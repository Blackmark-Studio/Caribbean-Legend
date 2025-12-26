// официантка Наталия Бушелл
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! E me disseram que você tinha se afogado... Mentirosos!";
				link.l1 = "Claro que sim! Ha! Eu estou bem!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia, "+GetAddress_Form(NPChar)+" ! Primeira vez por aqui? Nunca te vi antes... Espero que venha nos visitar mais vezes, o Sancho tem uma ótima variedade de bebidas. Ah, e meu nome é Nathalie, eu ajudo o Sancho com os assuntos da taverna.";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Prazer em te conhecer. Você não poderia ter me visto antes. Cheguei aqui há pouco tempo.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Tem algo interessante pra contar?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Até mais!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Recentemente? Outro navio naufragou? Não ouvi nada... Ou você chegou aqui como monsieur Turam, nos destroços do mastro? Ah, perdoe minha curiosidade, é coisa de mulher, sabe.";
			link.l1 = "Não, está tudo bem, Nathalie. Cheguei aqui em uma barca, mas ela afundou. Foi um prazer te conhecer. Até mais!";
			link.l1.go = "exit";
			link.l2 = "Não, tudo bem. Só queria te fazer umas perguntas sobre a ilha.";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estou ouvindo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Você trabalha na taverna. O que pode me contar sobre o dono?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "E como você veio parar aqui?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Quantas pessoas vivem aqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Você nunca se surpreende ao ver rostos novos por aqui?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Se me der licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Só coisas boas,  "+GetAddress_Form(NPChar)+" Sancho sempre tem uma grande variedade de bebidas – de vinhos antigos a simples cerveja e rum. Alguns anos atrás, ele encontrou um enorme estoque de vinhos raros. Sancho passou dois meses carregando caixas de garrafas para sua loja\nE agora estamos bem abastecidos com vinhos que só governadores podiam pagar lá no arquipélago. Rum também não falta. Sancho pode te oferecer não só bebidas, mas também as últimas novidades, um bom conselho e uma cama quente para passar a noite.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ah, essa é uma história triste. Sete anos atrás, fugi da casa dos meus pais com meu pretendente e decidimos nos mudar de Santiago para Belize. O navegador errou perto de Main, então seguimos na direção errada para o norte e fomos pegos por uma tempestade. Nosso navio afundou não muito longe do anel externo\nMeu pretendente morreu naquele dia, assim como a maioria dos outros. Os sobreviventes e eu começamos uma nova vida aqui, na Ilha da Justiça.";
			link.l1 = "Que história triste...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Quite a lot. The Rivados and Narwhal clans are strong in numbers; they've been living here for decades. There aren't many common folk, but the tavern is full every night. I barely manage to serve drinks.";
			link.l1 = "Sério? Interessante.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "E por que deveríamos? Sempre aparecem muitos rostos novos por aqui. Nem sei quantos de nós vivem neste lugar. Às vezes vejo alguém pela primeira vez e ele me diz que já mora aqui há um ano.";
			link.l1 = "Bem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você está fazendo aí, hein? Ladrão!","Olha só isso! Assim que me perdi em contemplação, você resolveu mexer no meu baú!","Veio fuçar nos meus baús? Não vai sair impune!");
			link.l1 = "Droga!";
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
			dialog.text = LinkRandPhrase("Olha, é melhor você guardar suas armas. Elas me deixam nervoso.","Sabe, andar por aí com uma lâmina na mão não é permitido aqui. Guarde isso.","Escuta, não fique bancando o cavaleiro medieval andando por aí com uma arma. Guarda isso, não combina com você...");
			link.l1 = LinkRandPhrase("Tudo bem.","Certo.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou um cidadão desta cidade e gostaria que você embainhasse sua espada.","Escute, eu sou um cidadão desta cidade e gostaria que você embainhasse sua espada.");
				link.l1 = LinkRandPhrase("Certo.","Certo.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, amigo, andando por aí com uma arma. Isso me deixa nervoso...","Não gosto quando as pessoas passam na minha frente com as armas em punho. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso embora.");
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
