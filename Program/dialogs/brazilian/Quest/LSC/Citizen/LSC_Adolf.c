// Адольф Барбье - авантюрист
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
				dialog.text = "Não quero nada com você. Você ataca civis inocentes sem motivo e provoca brigas. Cai fora!";
				link.l1 = "Hum...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Olá, olá... Nunca te vi por aqui. Novo?";
				link.l1 = "Quer dizer novo na ilha? Sim, você está certo. Meu nome é "+GetFullName(pchar)+", marinheiro e aventureiro.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Precisa de alguma coisa?";
				link.l1 = LinkRandPhrase("Tem alguma coisa interessante pra me contar?","Aconteceu algo novo na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Adeus!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha, igualzinho a mim. Não sou marinheiro, mas minha paixão por aventuras me trouxe até aqui. Agora vou apodrecer nesse cemitério de navios como todo mundo. Aliás, meu nome é Adolf Barbier.";
			link.l1 = "Foi bom te conhecer, Adolf. Adeus.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Tem algo interessante pra me contar?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Por que diabos você entrou na minha casa sem permissão?!";
			link.l1 = "Você está sendo pouco hospitaleiro com seu convidado, Adolf. Tenho assuntos a tratar com você.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "Eu não faço negócios com quem eu não conheço! Cai fora!";
			link.l1 = "Assim, do nada? Então você faz negócios com os Narvais, mas não comigo? Que pena...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "Do que você está falando, bobo? Que assunto você tem com os Narvais? Esta é sua última chance de sair antes que eu te jogue daqui!";
			link.l1 = "Você não tem coragem... Agora me escute! Onde está o stutzen que você vai usar para atirar no Almirante? Vai me contar por vontade própria ou preciso ser mais convincente?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "What? Are you mad, pal? I sold my stutzen - I don't have it anymore! And it's not your business whom I sold it to; I don't give a fuck what they do with it. And I'm not going to shoot anyone - admirals, generals, no one!. Do you understand me, fucker?";
			link.l1 = "Eu entendo que você é um mentiroso e um assassino, Adolf. Eu sei que você não vendeu, mas resgatou. Também sei que você recebeu uma grande quantia para pagar suas dívidas e comprar esta cabana--";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "Esse dinheiro é meu! Eu ganhei! E já vendi meu stutzen!";
			link.l1 = "Você está mentindo, Adolf. Os Narvais te contrataram para atirar no Almirante. Eles te deram dinheiro para resgatar seu stutzen. Também pagaram por este lugar. Você sabe melhor do que eu que o gurupés atrás desta porta é o único lugar na ilha de onde dá para atirar na varanda dos fundos da residência do Tubarão.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "Você está maluco, camarada! Deviam te internar! Estou esperando a Sessile sair desta cabine há meio ano--";
			link.l1 = "Chega! Vou revistar você e sua cabine, vou encontrar o stutzen – e outras provas também! – tenho certeza disso. E então iremos juntos ver o Tubarão. Ele vai olhar nos seus olhos e enxergar a verdade.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ah, seu desgraçado! Prefiro morrer do que deixar algum maluco imundo mexer nas minhas coisas!";
			link.l1 = "Está bem, então. Se você estiver morto, não vou precisar da sua permissão.";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Bem, vamos conversar. O que você quer saber?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "O que você pode me contar sobre os clãs locais?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Você já explorou o anel externo de navios?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "A ilha tem alguma ligação com Cuba ou com o continente?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Encontrei a crônica de um marinheiro espanhol, Ignacio Alvarado. Ele descreveu a ilha em detalhes, mencionando alguns navios em particular — San Augustine, San Geronimo e Tartarus. Todos faziam parte do esquadrão de de Betancourt, que desapareceu há mais de cinquenta anos. Pesquisei sobre a expedição. Descobri que havia um quarto navio chamado Santa Anna, que transportava o tesouro do esquadrão: uma pilha de dobrões! Além disso, os navios tinham minério de ouro em seus porões. Decidi encontrar a ilha. Fiz um acordo com um capitão conhecido e partimos na escuna dele. Você já deve imaginar como essa história termina: encontramos a ilha, os navios de de Betancourt, até mesmo o neto dele, Antonio de Betancourt. Desde então, estou aqui. A escuna se despedaçou nos recifes, meu companheiro morreu, e eu, junto com os outros sobreviventes, consegui nadar até aqui. O pior de tudo é que nunca encontrei o que procurava — nem o tesouro do Santa Anna, nem qualquer minério de ouro.";
			link.l1 = "História interessante. Também li a crônica de Alvarado.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "The Rivados are damned pagan scum. They're the offspring of negro slaves, brought here by de Betancourt from Africa. Even though they've learned how to use blades and muskets from us white folk, they're still savages.\nThe Narwhals are good people; smart, and decent fighters. They have outstanding craftsmen among them. I know a lot of them. Perhaps one day I'll join their clan.\nThe pirates are a pain in the arse - damn them! When they arrived, they captured our supplies and now dare to sell us our own food! Bastards, eh? Pity we don't have the numbers or skill to drive them away; we're stuck with the bloody lot of them.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sure. A man has to make coin. Damn pirates demand gold, pesos or other valuables for the food. They sell it more cheaply to locals like me than to the clans, but it's no charity. Thank God there are plenty of ships on the outer ring to loot; a lot of them still remain untapped since their wreckage.\nAn interesting activity, but dangerous; you may fall into a flooded hold, break bones, get tangled in ropes, smashed by wooden beams or eaten by giant crabs - they often roam the wrecks out there.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Infelizmente, não. Dizem que bucaneiros e contrabandistas de Cuba costumavam visitar este lugar com frequência, trocando mantimentos por ouro e destroços, e os Narvais às vezes partiam para visitar as colônias. Mas isso acabou. Hoje em dia, ninguém quer arriscar navegar em barcos pequenos e frágeis além do anel externo — as tempestades destruiriam tudo, e não temos embarcações melhores por aqui.";
			link.l1 = "Que pena...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você está fazendo aí, hein? Ladrão!","Olha só isso! Mal viro as costas, você já decide vasculhar meu baú!","Resolveu saquear meus baús, é? Você não vai sair impune disso!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Veio saquear meus baús? Você não vai sair impune disso!";
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
			dialog.text = LinkRandPhrase("Olha, é melhor você guardar sua arma. Isso me deixa nervoso.","Sabe, andar por aí com uma lâmina não é permitido aqui. Guarde isso.","Escuta, não fique bancando o cavaleiro correndo por aí com uma espada, isso não combina com você. Guarde isso...");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você diz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou um cidadão da cidade e peço que abaixe sua lâmina.","Escute, sou um cidadão da cidade e peço que abaixe sua lâmina.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, camarada, andando por aí com uma arma dessas. Isso me deixa nervoso...","Eu não gosto de homens apontando armas na minha cara. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Vou guardar isso.");
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
