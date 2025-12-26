// Таннеке Эверс - просто девушка
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
				dialog.text = "Me deixe em paz, senhor. Não quero conversar com um homem que ataca pessoas pacíficas!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia! Eu te conheço? Acho que nunca te vi antes...";
				link.l1 = TimeGreeting()+". Eu sou novo aqui, é verdade. Meu nome é Capitão "+GetFullName(pchar)+"";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Oi, Tanneke. Quais são as novidades na ilha?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Tenha um bom dia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ex-capitão. (risada)";
			link.l1 = "What do you...? A-ha, I understand. No, I'm still a captain; my ship is moored off the shores of the Spanish Main. I reached this place on a barque - or, almost reached it; the barque was hold and sunk two miles offshore.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "E como você conseguiu sobreviver às tempestades?";
			link.l1 = "Que tempestades? Eu não me lembro de nenhuma tempestade...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Como não saber? Sempre há tempestades ao redor da ilha. Todo mundo diz isso.";
			link.l1 = "Bem... acho que tive sorte de escapar disso. O mar estava absolutamente calmo... com licença, posso saber o nome de uma dama tão bonita?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Oh! Me desculpe, esqueci de me apresentar... Meu nome é Tanneke. Prazer em te conhecer.";
			link.l1 = "Prazer em te conhecer também, Tanneke... Encantado, de verdade.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "E por que você trocou seu navio por uma barca?";
			link.l1 = "Ouvi rumores sobre a Ilha da Justiça e decidi ver com meus próprios olhos. Não quis arriscar meu navio, então o deixei ancorado em Blueweld e comprei uma barca para explorar esta região...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Agora entendi. Você é igualzinho ao Adolf Barbier: leu demais sobre o Capitão Alvarado e resolveu procurar o ouro do Almirante de Betancourt. Mas, capitão, se até um trapaceiro esperto como o Barbier não conseguiu achar, duvido que você consiga.  E pra falar a verdade, nem acho que exista esse ouro do almirante. Acho que o Antonio inventou essa história só pra fazer o avô dele parecer importante.  Bem, então vai ficar aqui com a gente! Chegar até aqui foi fácil, mas sair... impossível — pelo menos inteiro.";
			link.l1 = "Ouro? Almirante de Betancourt? É a primeira vez que ouço falar disso... De qualquer forma, pretendo sair da ilha — inteiro. Foi um prazer conversar com você, Tanneke. Adeus!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Pode perguntar, Capitão...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você já tentou sair da ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Como é a sua vida aqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Er... as mulheres precisam comprar comida do Almirante, ou recebem de graça?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Sou holandesa de nascimento, mas vivi em Santiago. Meus pais me mandaram trabalhar lá como criada para a família de banqueiros Geraldi. Já ouviu falar deles? Três anos atrás, um deles partiu para a Nova Espanha em uma escuna-correio. Fui instruída a acompanhá-lo. No segundo dia da viagem, fomos abordados por uma escuna sob bandeira espanhola. O oficial deles subiu a bordo e conversou com nosso capitão — sobre o quê, não sei. O capitão ficou furioso e expulsou o oficial do navio. Quando o oficial voltou para sua embarcação, eles abriram fogo contra nós. Tentamos fugir, mas conseguiram nos abordar. Acho que estavam atrás do meu patrão, Geraldi, porque correram direto para a cabine dele, o algemaram e o levaram embora. Eu e a tripulação fomos jogados no porão e trancados lá. Achei que iam afundar o navio, mas simplesmente partiram. Os marinheiros conseguiram escapar do porão. Encontramos o capitão morto no convés. Nenhum de nós sabia navegar direito. Navegamos sem rumo até que uma forte tempestade nos atingiu. Poucas horas depois, nossa escuna foi arremessada contra o anel externo. Ela ainda está lá. Ao amanhecer, eu e alguns poucos sobreviventes subimos no bote e remamos até a ilha.";
			link.l1 = "Que história!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Não. Como eu saberia? Não há navios em condições de navegar, e tentar sair numa chalupa é suicídio. Como eu disse, a ilha é cercada por tempestades. Cinco moradores já tentaram fugir desse jeito. Construíram uma boa chalupa com madeira resistente e velas aproveitadas de um Indiaman naufragado. Lutaram contra a corrente por nove horas até conseguirem chegar em mar aberto. Alguns dias depois, um deles apareceu de volta no anel externo, amarrado ao que restou do mastro... morto, feito pedra. Depois disso, pouca gente teve coragem de tentar fugir.";
			link.l1 = "Horrível...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Está tudo bem. Não é pior do que ser criado daquela família de agiotas arrogantes. Só precisa se acostumar com este lugar, e, quando isso acontecer, pode até acabar gostando daqui. Muitos sentem o mesmo. E as facções, elas não me incomodam.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Claro que compramos. Tem trabalho de sobra para uma moça: limpar, cozinhar, ajudar os outros... não ficamos à toa, mas também não nos matamos de trabalhar. Os piratas vendem comida barata para o povo, diferente do que fazem com os clãs, que eles exploram sem piedade. Então, não passamos fome. Eu ajudo a Gillian e a Natalie, e elas me ajudam quando preciso. Somos amigas. Tem outra moça na ilha, uma espanhola: Ramona. Mas ela é mais na dela e a gente também não faz muita questão de ser amiga dela.";
			link.l1 = "E por que isso?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Bem... digamos que temos visões diferentes sobre a vida. Converse com ela e você vai entender.";
			link.l1 = "Tudo bem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Quem é... ai meu Deus, ladrão! Socorro!","Viro as costas por um minuto e você tenta me roubar?! Socorro!","Resolveu saquear meus baús? Você não vai sair impune dessa!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Como você ousa mexer nas minhas coisas! Alguém, ajude!";
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
			dialog.text = LinkRandPhrase("Por favor, guarde sua arma, senhor. Você está me deixando nervoso.","Sabe, andar por aí com uma lâmina não é permitido aqui. Guarde isso.","Senhor, eu sei que você é valente. Não precisa provar isso brandindo uma espada...");
			link.l1 = LinkRandPhrase("Tudo bem.","Como quiser...","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Por favor, guarde sua arma, senhor. Você está me deixando nervoso.","Sabe, andar por aí com uma lâmina na mão não é permitido aqui. Guarde isso.");
				link.l1 = LinkRandPhrase("Tudo bem.","Como quiser...","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Por favor, guarde sua arma, senhor. Você está me deixando nervoso.","Mynheer, eu sei que você é valente. Não precisa provar isso brandindo uma espada...");
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
