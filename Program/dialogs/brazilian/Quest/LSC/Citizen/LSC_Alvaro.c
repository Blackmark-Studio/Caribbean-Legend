// Альваро Гомец - капитан
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
				dialog.text = "Senhor, não direi nada a você! Você ataca gente pacífica sem motivo. Vai pro inferno!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, um rosto novo! Seja bem-vindo! E quando foi que você chegou? Não me lembro de nenhum naufrágio recente.";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". E meu navio afundou rápido e silenciosamente naquela noite. Só eu, de toda a minha tripulação, consegui nadar até a ilha...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Tem alguma coisa interessante pra me contar?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Adeus!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Entendo. Ah, esqueci de me apresentar. Perdão, senhor. Meu nome é Alvaro Gomez e já fui capitão de uma brigue. Eh, agora meu belo navio está no fundo do mar, logo além do anel externo... Muita água já passou por baixo da ponte desde então. Ah, así es la vida. Prazer em conhecê-lo!";
			link.l1 = "Prazer em conhecê-lo também, Señor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Tem alguma coisa interessante pra me contar?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estou ouvindo, señor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Você disse que já foi capitão. Como veio parar na ilha?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "O que você pode me contar sobre a vida na ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Me diga, os moradores daqui vivem em paz uns com os outros? Tirando os clãs, é claro.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "De onde os moradores conseguem mantimentos?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Como aconteceu com todos os outros: fui pego pelas tempestades. Perdi o mastro e o leme, depois a correnteza nos arrastou e nos lançou nos recifes. Meu navio nem chegou ao anel externo antes de ser destruído. Só alguns homens sobreviveram, eu incluso.";
			link.l1 = "História triste...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "O que posso dizer? Temos tudo o que precisamos para viver. Às vezes, porém, a vida aqui fica bem monótona, e essa melancolia... o primeiro ano foi realmente difícil. Mas acabei me acostumando com a ilha. Sinto muito pela minha pobre esposa Sabrina – ela deve pensar que estou morto. Espero de verdade que ela tenha conseguido se casar de novo, e que esteja feliz.  Não fique abatido com sua situação, mi amigo, você vai se acostumar. Visite a taverna, a loja, a igreja, conheça todo mundo – mas não vá até os Narvais ou os Rivados a menos que seja realmente necessário! Eles são uns sujeitos traiçoeiros.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "De modo geral, vivemos em paz. Não temos leis escritas, mas se você agredir alguém sem um bom motivo ou, Deus me livre, cometer um assassinato, será isolado. Pode até ser jogado ao mar durante a noite. Já houve alguns briguentos sem clã na ilha – verdadeiros canalhas. O primeiro sumiu, e o segundo morreu nas celas do Tártaro depois de alguns meses apodrecendo lá dentro. Isso não quer dizer que você não possa se defender de um ataque violento, mas, no geral, o povo daqui é bem tranquilo. O Abade gosta de se exibir, mas não é agressivo. Kassel é um bastardo, mas mantém as mãos limpas. Pratt é um ex-presidiário, mas é inofensivo. Temos dois ex-oficiais da marinha aqui – Lauderdale e Solderra. Eles vieram parar aqui durante uma batalha naval perto da ilha. Os dois sobreviveram e continuam tramando planos sangrentos um contra o outro.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Dos porões dos destroços, de fato. Todas as provisões costumavam ser guardadas no San Augustine e divididas igualmente. Depois vieram os piratas e tomaram o San Augustine — agora eles apertam a ilha por dinheiro para pagar pelas mesmas provisões que já foram nossas!\nTemos nossos próprios esconderijos, então não passamos fome. Também pescamos e caçamos pássaros, mas a melhor carne vem dos caranguejos gigantes. Eles têm uma carne muito saborosa e nutritiva — embora raramente se aproximem do anel externo.\nMergulhar para caçá-los é arriscado demais. Uma vez houve um homem corajoso o bastante para caçá-los debaixo d’água, mas a sorte dele, no fim, acabou. Ninguém mais mergulhou atrás de carne de caranguejo desde então.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ladrão! Thief!","Você acha que pode simplesmente pegar o que quiser?! Enfrente o aço!","Como você ousa roubar minhas coisas! Prepare-se para minha espada!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Veio saquear meus baús? Você não vai sair impune dessa!";
			link.l1 = "Maldita garota!";
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
			dialog.text = LinkRandPhrase("Ai, caramba! Guarde sua arma, hombre!","As pessoas aqui não gostam muito de quem anda por aí com a espada desembainhada.","Escute, caballero, não é seguro andar por aí com a espada desembainhada. Guarde-a...");
			link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você diz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Como cidadão desta cidade, peço que guarde sua lâmina.","Como cidadão desta cidade, peço que guarde sua lâmina.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tanto faz então.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Tome cuidado, mi amigo, andando por aí com uma arma dessas. Você me deixa nervoso...","Não fique balançando sua arma assim na minha frente. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendido.","Estou guardando isso.");
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
