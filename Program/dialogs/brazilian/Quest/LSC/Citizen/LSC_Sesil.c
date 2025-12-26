// Сесил Галард - бабулька
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Não quero falar com você. Você ataca civis inocentes sem motivo e ainda provoca briga. Cai fora!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Quer alguma coisa, rapaz?";
				link.l1 = TimeGreeting()+". Deixe-me me apresentar - "+GetFullName(pchar)+". Eu sou um recém-chegado.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! O que posso fazer por você?";
				link.l1 = LinkRandPhrase("Olá, Cecille. Ouviu alguma fofoca interessante ultimamente?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Até mais!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A-ah, então você está conhecendo nossa ilha e seus habitantes?";
			link.l1 = "Exatamente, madame?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Prazer em conhecê-la, Madame Halard! É um prazer.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A minha também... E como você veio parar aqui, rapaz? Não me lembro de nenhum naufrágio recente...";
			link.l1 = "Eu naveguei do continente espanhol em uma barca e uma tempestade me trouxe até aqui... meu navio afundou não muito longe da ilha.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Nesse caso, você teve muita sorte de chegar à ilha inteiro. As tempestades raramente atingem a ilha em si, mas nas águas ao redor elas podem surgir do nada e afundar até os navios mais resistentes!\nEntão considere-se sortudo e comece a se acostumar com o lugar. Não quero te desanimar, mas chegar aqui é fácil; sair da ilha é quase impossível. Ninguém conseguiu fazer isso — e sobreviver — nos últimos dez anos.";
			link.l1 = "Me perdoe, mas não vou me entregar ao desespero tão facilmente. Foi um prazer conhecê-la, Madame Halard, até a próxima!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sim, rapaz?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "E como a senhora veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você já mora aqui faz tempo, não é?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "O que você pode me contar sobre os moradores daqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Quem são as pessoas mais interessantes que vivem aqui?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Foi há tanto tempo, mal me lembro de como aconteceu. Sei que naufraguei, mas quanto aos detalhes... (dá de ombros)";
			link.l1 = "Hã.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Desde que eu era uma garotinha. Às vezes, quase acredito que nasci aqui... mas isso não é verdade, claro. Porém, com certeza vou morrer aqui.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Não há muito o que eu possa dizer, rapaz... A Ilha da Justiça abriga todo tipo de gente: brancos, negros, índios, escravos fugitivos, nobres, condenados do Estado, marinheiros... e já teve ainda mais gente antes. Cada um tem sua história e seus costumes. Tem quem esteja feliz por estar aqui, e tem quem só pense em ir embora.\nAí tem os clãs – Narvais e Rivados – e os piratas equilibram as coisas. Você vê aqui uma mistura de pessoas que não existe em nenhum outro lugar do mundo, e vivem em relativa paz e harmonia também...";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Herr Schmidt, o mecânico-inventor dos Narvais... Sancho Carpentero, o barman local... E agora também temos o Almirante Tubarão Dodson com seu amigo, Layton Dexter.\nMas, sinceramente, você deveria ir conhecer algumas dessas pessoas por conta própria. Você não faz ideia de quantas histórias interessantes nós, moradores da Ilha da Justiça, temos.";
			link.l1 = "Vou pensar nisso...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah, ladrão! Pare aí!","Assaltar uma senhora idosa pelas costas? Que vergonha!","Resolveu saquear meus baús? Você não vai sair impune!");
			link.l1 = "Droga!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Assaltar uma velha pelas costas? Como você se atreve!!";
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
			dialog.text = LinkRandPhrase("Guarde sua arma, rapaz. Isso me deixa nervoso.","Sabe, coisas ruins acontecem com quem fica balançando armas por aqui. Guarda isso.","Rapaz, guarde sua espada. Você vai assustar uma velha até a morte!");
			link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você diz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Guarde sua arma, rapaz. Isso me deixa nervoso.","Sabe, coisas ruins acontecem com quem fica balançando armas por aqui. Guarda isso.");
				link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Guarde sua arma, rapaz. Isso me deixa nervoso.","Rapaz, guarde sua espada. Você vai assustar uma velha até a morte!");
				link.l1 = RandPhraseSimple("Desculpe.","Estou guardando isso.");
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
