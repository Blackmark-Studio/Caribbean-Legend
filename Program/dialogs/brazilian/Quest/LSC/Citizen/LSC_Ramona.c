// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Vá embora, señor. Você ataca pessoas comuns que só querem cuidar da própria vida.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ora, ora! Ou você é novo por aqui, ou estava se escondendo em algum dos porões de carga, porque é a primeira vez que vejo seu rosto por aqui.";
				link.l1 = TimeGreeting()+". Esconder-se nos porões de carga não é o meu estilo. Prefiro a cabine do capitão... Mas sim, sou novo aqui.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! "+TimeGreeting()+"! Fico feliz em te ver! O que me diz?";
				link.l1 = LinkRandPhrase("Querida Ramona! Como vão as coisas na ilha?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria ver seu rosto lindo. Até a próxima, Ramona!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Vamos nos conhecer então... Capitão. Eu sou Ramona Lozano – e nem pense em me chamar de 'Senhora' Lozano. Eu detesto isso. Qual é o seu nome?";
			link.l1 = ""+GetFullName(pchar)+". Prazer em conhecê-la, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Você está mesmo feliz ou só está sendo educado, "+GetFullName(pchar)+"? Me diga, você é mesmo um capitão ou estava brincando?";
			link.l1 = "O-ho, so many questions! May I answer them in order? First, I am truly delighted; I don't meet such pretty girls every day. Second, I am indeed a captain, but my ship is anchored on the coast of the Spanish Main right now.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Engraçado! E como é que o senhor está aqui, capitão, enquanto seu navio está na costa do continente? Não tem medo de que sua tripulação se disperse e alguém tome seu navio?";
			link.l1 = "Vim para cá em uma barca para... explorar esta parte do mar. Não quis arriscar meu navio — ele é meu orgulho e alegria. Mas à noite, a barca bateu em algum recife ou destroço na escuridão, virou, et voilà! Aqui estou eu.  Meu navio vai me esperar o tempo que for preciso. Dannie Hawk vai manter os rapazes unidos.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk? Quer dizer... Danielle Hawk? Você está me dizendo que navega com ela?";
			link.l1 = "My hand to God, Ramona, I tell no lie; Dannie serves as my officer. I left her in command while I set out in my barque... How do you know her?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha! Todo mundo nas colônias espanholas conhece a pirata Danielle Hawk e o marido dela, Nathaniel. Sim, você, señor "+GetFullName(pchar)+", deve ser um homem durão... Então você é pirata? Não se preocupe, eu me dou muito bem com gente como você. Gosto de homens fortes.";
			link.l1 = "Bem, eu não sou exatamente um pirata... no momento estou trabalhando para o Jan Svenson – tentando ajudar a Dannie a encontrar o marido desaparecido dela.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "E você diz que não é um pirata? Trabalha para o Diabo da Floresta, sua imediata é a Danielle Hawk, está procurando por Nathaniel... e tenho certeza de que veio aqui por causa do Almirante. Certo?";
			link.l1 = "Ramona, pode me chamar de pirata se quiser. Pode até me chamar de âncora – só não vá me usar como uma!";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Parece que você é mesmo um desses homens realmente duros, "+pchar.name+". Bem, eu preciso ir. Espero te ver pela ilha, sinto que podemos ser amigos... amigos de verdade.";
			link.l1 = "Por que não? Bom dia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ah, é mesmo? Então, pergunte. Vou responder se puder...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Com certeza você já tentou deixar a ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Como você vive aqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "O que você faz aqui? Imagino que a comida não seja de graça, certo?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Essa é uma longa história... A culpa é do meu padrasto.\nQuatro anos atrás, eu vivia feliz em Havana. Minha mãe morreu e eu fui o único herdeiro da fortuna dela. Não éramos ricos, mas tínhamos dinheiro — mais do que o suficiente para viver bem.\nMeu padrasto não gostou nada disso e decidiu se livrar de mim. Claro, só descobri depois que dois capangas me atacaram nos portões da cidade. Aqueles idiotas me contaram eles mesmos quem os contratou para me matar e por quê.\nPor sorte, não eram profissionais, senão eu estaria largado nos arbustos com a garganta cortada. Os imbecis quiseram se divertir antes.\nO destino me salvou: um capitão como você passou por ali na hora. Ele viu o que estava acontecendo e matou aqueles vermes na hora — eles não tiveram chance. Contei a ele minha situação, chorei um pouco... Ele percebeu que eu não tinha para onde ir, então me levou a bordo do navio para me salvar do meu padrasto — a princípio só por um tempo, mas depois...\nAcho que teria ficado com ele, mas dois meses depois ele cruzou com uma patrulha, perdeu um mastro, foi pego por uma tempestade forte e encontrou seu fim no fundo do anel externo. Eu sobrevivi, apesar de tudo, e acabei me juntando à comunidade da Ilha da Justiça.";
			link.l1 = "Que história triste, fico sem palavras.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Claro que não, porque é impossível. Vi um homem que tentou sair daqui em um bote... ele voltou dois dias depois. Tinha se amarrado a um mastro quebrado para não se afogar, mas estava azul e morto como pedra.\nE me diga, "+pchar.name+", o que eu deveria fazer mesmo se conseguisse fugir? Havana é perigosa demais pra mim – meu padrasto com certeza tentaria me matar de novo. Não tenho casa, nem dinheiro. Pra onde eu iria? Pra um bordel?";
			link.l1 = "Mesmo assim, você quer voltar para o Caribe?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "O que você acha? Claro que sim. Mas é impossível, e acabei de te explicar o motivo. Se alguém conseguisse dar um jeito no meu padrasto – seja na ponta da lâmina ou na bala –, talvez eu ainda tivesse esperança de voltar pra minha antiga vida. Mas quem teria coragem de fazer isso, sabendo que meu padrasto é amigo íntimo do governador de Havana? Então, do que estamos falando? Não tem saída daqui...";
			link.l1 = "Vamos ver. Talvez chegue a hora...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Eu simplesmente vivo. Não há outra opção. Meus amigos são quase todos homens porque as nossas duas beldades casadoiras – Gillian e Tanneke – não gostam de mim. A Natalie era uma boa garota até começar a passar muito tempo com aquelas duas idiotas. Burrice pega.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "I work like the other girls, mostly helping the men. There's a lot of work for women on the island so I keep busy. And I often get gifts - it's a usual thing here. But don't think I am some wench; I was well educated and come from a good family. I just don't play the saint... like some women...";
			link.l1 = "Eu não estava pensando mal de você, de jeito nenhum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você está fazendo - ah! Ladrão!","Olha só isso! Mal viro as costas, você já resolve vasculhar meu baú!","Revirando meus baús?! Você não vai sair impune disso!");
			link.l1 = "Droga!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Filho da puta! Invadindo meu baú enquanto viro as costas?!";
			link.l1 = "Fique quieto!";
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
			dialog.text = LinkRandPhrase("Senhor, guarde sua arma. Isso me deixa nervoso.","Não gostamos quando idiotas ficam correndo por aí com a espada desembainhada. Guarde isso.","Você parece um idiota correndo por aí com a espada desembainhada. Guarda isso...");
			link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escuta, guarda essa lâmina. Você está assustando as pessoas.","Não gostamos quando idiotas ficam correndo por aí com a espada desembainhada. Guarde isso.");
				link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Senhor, guarde sua arma. Isso me deixa nervoso.","Você parece um idiota correndo por aí com a espada desembainhada. Guarda isso...");
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
