// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia, senhor. Nunca o vi por aqui antes. Você é novo aqui? É a primeira vez que visita esta plataforma?";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+".   Sou novo aqui, só estou dando uma olhada e conhecendo as pessoas...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Escute, "+pchar.name+", se você continuar me distraindo, nunca vou terminar os consertos.";
					link.l1 = "Sim, sim, eu me lembro disso. Me desculpe por incomodar você!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ah! Olha só isso! O afogado voltou do outro mundo! Agora me diga, como conseguiu esse feito? Fizeram até um funeral pra você e te enterraram na sua ausência, caso não soubesse...";
					link.l1 = "Que pena, mas ainda não vou morrer. O truque é simples – só toquei o ídolo de Kukulcan na base. Ele me teleportou para Dominica, bem no meio da aldeia dos Caribes...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik, tenho uma proposta de negócio para você. Uma proposta muito importante. Ole Christiansen me falou sobre você. Ele também é conhecido como o Menino Branco.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, trouxe a você prata suficiente. Exatamente como pediu: um dos seus, mais dez peças extras. Aqui, pegue.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Sou eu de novo, Henrik. Como está o seu traje? Conseguiu consertá-lo?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "Tenho o metal suficiente, aquele que você pediu. Pegue.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Bom dia, Henrik. Então, o traje está pronto para o mergulho?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "Acabou, resolvi meus problemas e estou pronto para mergulhar. Quando começamos?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Olá, Henrik. Então, o traje está pronto para o mergulho?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Quero devolver seu traje.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Tem alguma coisa interessante pra contar?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Eu só queria saber como você está.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "E eu sou Henrik Vedecker. Mas a maioria dos moradores me conhece como o Mecânico, e isso me descreve muito bem.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Você é Henrik Vedecker? Prazer em conhecê-lo! Eu estava procurando por você.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Você deve ser o faz-tudo, certo?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Ah, sim, os Narvais realmente valorizam minhas habilidades. Minhas ferramentas permitem que eles recuperem muitos objetos valiosos dos navios perdidos do anel externo, assim podem comprar mantimentos do Almirante Dodson\nNa verdade, minha paixão é a ciência e a exploração. Por isso, peço desculpas se não conseguir passar muito tempo com você – meus experimentos consomem quase todo o meu tempo.";
			link.l1 = "Entendo. Não vou incomodá-lo sem motivo, senhor Vedecker, pode ter certeza. Fico muito feliz em conhecê-lo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Era mesmo? E por quê?";
			link.l1 = "Ole Christiansen me falou sobre você. Ele também é conhecido como o Garoto Branco.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ah, aquele sujeito engraçado! Sim, sim, eu conheço ele. E o que ele te contou?";
			link.l1 = "Me desculpe se minha próxima pergunta parecer boba, mas... vou perguntar mesmo assim. O Ole me disse que talvez você possa me ensinar a mergulhar até o fundo, debaixo d'água. Por favor, não ria de mim se isso for só coisa da cabeça dele.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "É verdade. Eu mesmo já estive no fundo várias vezes. Mas não mergulho mais, o banco está cheio de caranguejos gigantes hoje em dia e, como pode ver, não tenho condições de enfrentá-los. Sou um cientista, não consigo lutar contra essas criaturas. Além disso, havia também dois outros homens, dois Narvais, que costumavam mergulhar, mas acabaram desistindo — saquear os porões dos navios do anel externo acabou sendo mais seguro do que descer até um lugar infestado de caranguejos gigantes. Agora eles quase não usam mais meu equipamento, não houve um único mergulho nos últimos meses por causa da rachadura no traje...";
			link.l1 = "Você tem mesmo um traje que te deixa mergulhar até o fundo? Ouvi direito?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Seus ouvidos estão no lugar certo, rapaz. Fui eu quem inventou e construiu o traje. Ele é feito de lona grossa, totalmente encharcada e completamente à prova d'água, com peças de metal e um capacete de aço que eu e Jurgen forjamos na oficina dele\nTambém reforcei o traje com uma placa de metal no peito, proteções nos joelhos, no peito e botas, para garantir mais proteção contra caranguejos e mais peso\nCilindros especiais, cheios de ar pressurizado, garantem suporte vital e permitem passar um tempo debaixo d'água. O traje é único, e eu me orgulho muito dele.";
			link.l1 = "Isso é ótimo. Mas você mencionou que o traje está danificado?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Infelizmente, é verdade. Várias partes do traje eram conectadas por placas de metal para dar flexibilidade e proteção extra, mas a água do mar as afetou bastante. As placas enferrujaram depois de anos de uso e perderam suas propriedades à prova d'água.\nAinda bem que percebi o dano a tempo e evitei que alguém morresse. Mesmo o traje seco tinha um pouco de sal e água, que já tinham causado estragos.";
			link.l1 = "Bem... Mas você pode consertar o traje! Pode trocar as peças velhas e enferrujadas por novas... Não é?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Para quê? Para ter que trocar tudo de novo daqui a um ano? Você faz ideia de como esse trabalho é difícil? Montar o traje com articulações flexíveis e deixá-lo à prova d’água? Isso leva pelo menos uma semana sem descanso.";
			link.l1 = "E é por isso que você está disposto a abrir mão da sua invenção?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "Não, claro que não. Eu tive uma ideia. Preciso fazer as juntas de um metal que não possa ser destruído pela água ou pelo sal. E eu sei qual metal pode ajudar...";
			link.l1 = "Então qual é o problema?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "O problema é que esse metal é muito raro. Eu só tenho uma peça, o que certamente não é suficiente. Preciso de pelo menos mais dez peças, talvez até quinze.";
			link.l1 = "E o que é esse... metal de que você está falando?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "Oh, este é um metal único, realmente subestimado por muitos. Tem alta durabilidade, maleabilidade, e é absolutamente imune à exposição – nem a água nem o sal conseguem danificá-lo\nTalvez você já tenha visto este metal antes. Ele é branco, parece prata, por isso os espanhóis o chamaram de 'prata'. Ha! É cem vezes melhor que a prata! Melhor até do que o ouro! Um dia eles vão entender isso, mas ainda não chegou a hora certa.";
			link.l1 = "Escuta, por que você não usa outros tipos de metal então? Por que não faz essas placas de ouro? Nunca ouvi dizer que ouro enferruja ou estraga.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "Você tem uma mente flexível e viva, rapaz. Isso é bom de saber. Infelizmente, sua proposta não vai funcionar. A ideia do ouro também foi a primeira que me veio à cabeça. Mas o ouro é macio demais para unir as diferentes partes do traje.\nInfelizmente, só a platina serve para isso. Vou fabricar as peças apenas com ela, mesmo que leve anos para juntar o suficiente. Mas já vi pedaços desse metal antes na Ilha da Justiça — ele costuma aparecer misturado à prata por causa da aparência.";
			link.l1 = "Hum. E se eu te ajudar a encontrar bastante dessa... 'prata', você me empresta o traje pra eu mergulhar?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Não precisa nem pedir! Claro que eu vou. Já te falei que não mergulho lá por causa dos caranguejos, e ninguém mais quer ir também.";
			link.l1 = "Então me mostre esse pedaço de metal para que eu entenda o que preciso encontrar.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "So you are going to search for it? Excellent. Here, take this piece as an example. Look for it among the silver ore and nuggets. It won't be easy to find, but you'll manage. There are small dark spots on silver, but our metal is clear and much harder than silver. The easiest way to test it is by scratching a silver coin on it; if the coin gets damaged, then you've found it.";
			link.l1 = "Tá bom. Vou procurar por isso imediatamente. Tem alguma dica de onde devo procurar?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "Infelizmente, não sei. Se eu soubesse onde encontrar, já teria feito isso eu mesmo. Mas posso te dar um conselho. Procure nos navios dos Rivados. Eu não costumo ir lá, então é bem provável que eles tenham o que você procura.";
			link.l1 = "Vou pensar nisso, Henrik. Espero ter sorte.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Recolha mais dez peças. Esse é o mínimo necessário para consertar o traje. Boa sorte!";
			link.l1 = "Obrigado. Adeus, Mecânico!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Muito bem, mostre-me... Excelente! Muito bom, rapaz! Foi difícil?";
			link.l1 = "Na verdade, não...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Bem, agora posso começar os reparos. Não vou perder tempo e começo amanhã. Você está mesmo ansioso para mergulhar, não é?";
			link.l1 = "Com certeza. Eu quero muito explorar o fundo do mar.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "Isso é muito bom, porque vou precisar te pedir um favor quando organizarmos o seu mergulho. Mas falamos sobre isso depois. Venha me ver em cinco dias, espero já ter terminado os consertos.";
			link.l1 = "Certo. Boa sorte pra você!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "Sorte é sempre bem-vinda, mas o conserto da armadura vai depender mais de habilidade. Além disso, vou precisar passar um dia inteiro perto da fornalha com o Jurgen para transformar o metal que você trouxe em placas.";
			link.l1 = "Então não vou te incomodar. Nos vemos em cinco dias. Adeus!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Sim. Jurgen e eu fizemos um trabalho e tanto, e a quantidade de peças que você trouxe foi suficiente para isso. O traje está consertado e pronto. Só preciso fazer alguns testes, mas tenho certeza de que está tudo certo. Venha amanhã às 10 da manhã — vou encher os tanques de ar e você poderá fazer o que quiser.";
				link.l1 = "Excelente! Estou ansioso por isso. Até amanhã, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Tenho que te decepcionar, "+pchar.name+".   Como eu suspeitava, não há metal suficiente. Eu preciso "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+" mais peças para terminar o conserto. Vou ter que pedir sua ajuda de novo.";
				link.l1 = "Pois bem, não esperava por essa reviravolta. Tudo bem, vou tentar encontrar as pepitas que te faltam.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Eu vou esperar por você. Pode ter certeza de que essa quantia será suficiente. Só traga eles e eu termino o trabalho em um dia.";
			link.l1 = "Espero que sim... Até mais!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Excelente! Agora o traje será restaurado. Só preciso fazer alguns testes, mas tenho certeza de que está tudo certo. Volte amanhã às 10 da manhã – vou encher os tanques de ar e você poderá fazer o que quiser.";
			link.l1 = "Excelente! Estou ansioso por isso. Até amanhã, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Sim, o traje está pronto e cheio de ar. Você pode mergulhar.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Está bem. Mas não posso mergulhar agora, preciso resolver um problema relacionado ao meu... amigo, Nathan Hawk. Não consigo encontrá-lo. A roupa pode esperar um pouco?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Excelente! Quando começamos? Agora?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Claro. Pode esperar. Você vai procurar seu amigo por um ano inteiro?";
			link.l1 = "Claro, não vou. Talvez eu o encontre ainda hoje. Vou te visitar assim que terminar meus assuntos com ele.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Sim, por favor. Venha quando estiver pronto para mergulhar.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Right now, if you want. But let me give you a little instruction first. You will start your dive from the 'Phoenix' platform; you can get there from the San Gabriel's stern. There is a hoist that will take you to the bottom and back. This is the only way to return\nSo you'd better remember the location of the hoist underwater and don't get lost. The suit's tanks have enough air for twenty minutes of diving. Watch your time or you'll suffocate\nDon't stray too far from the hoist or you won't be able to return in time, and God save you if you leave our shoal – you'll be flattened like a flatfish\nBe careful and watch out for crabs. If you get too close, they'll attack you. Don't take risks if you don't have to; you won't be able to kill a whole pack of them, and running away quickly is not an option down there.";
			link.l1 = "Eu cuido dos caranguejos. O resto é comigo. Não mergulhe muito fundo, não se afaste do guincho e não perca a noção do tempo. Quando posso mergulhar?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Quando quiser, mas só das 7 da manhã até as 9 da noite. Você não vai enxergar nada no escuro.";
			link.l1 = "Entendi.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "That's just it. Take the suit from the room by the platform. Take it off after a dive and bring it to me. I will fill it with air again. But don't try to dive more than once per day; even 20 minutes of diving and breathing compressed air is bad for your health.";
			link.l1 = "Bem, então não vou mergulhar mais de uma vez por dia.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Fico feliz que você entenda. Agora vá, e boa sorte!";
			link.l1 = "Obrigado!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Então, por que você ainda está aqui? O terno está esperando por você.";
				link.l1 = "Sim, sim. Já estou indo.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "E então, como foi o primeiro mergulho?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Muito bom, estou satisfeito com os resultados. Encontrei um ídolo de pedra no galeão afundado. Ouvi dizer que os Rivados já fizeram algumas oferendas a ele antes. Diga-me, Henrik, você conhece alguém que possa me contar mais sobre isso?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "Tá bom. Eu fiz isso! Foi bem interessante, embora um pouco emocionante.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Está interessado na nossa história? Procure Antonio Betancourt. Ele nasceu aqui. Mora na flauta Pluto. Se ele não souber nada sobre isso – ninguém sabe.";
			link.l1 = "Excelente! Com certeza vou fazer uma visita a ele.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Deixe o traje aqui. Volte amanhã ou em qualquer outro dia, eu vou enchê-lo de ar.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Claro. Aqui está seu traje. Obrigado!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Com certeza. Vou trazer imediatamente!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Então, você trouxe meu equipamento?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Claro. Aqui está seu traje. Obrigado!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Vou fazer isso agora mesmo!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Sim, claro. O traje foi testado e está cheio de ar. Você trouxe a garantia? 500.000 pesos?";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "Sim, claro. Aqui, pegue.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Opa! Esqueci disso. Vou trazer agora mesmo...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Sim, claro. O traje foi testado e está cheio de ar. Verifique a plataforma 'Fênix' como de costume.";
				link.l1 = "Então eu vou mergulhar. Obrigado!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Tudo bem. Volte amanhã ou mais tarde. Vou preparar o traje.";
			link.l1 = "Obrigado, Mecânico!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Você vai receber seu dinheiro de volta quando devolver o traje. Justo, não é?";
			link.l1 = "Obrigado, Mecânico! Agora vou mergulhar.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Espere um segundo, por favor! Que estátua? A-ah, agora entendi. Você está falando daquele ídolo no navio afundado 'San-Geronimo', não é? Então aquelas histórias dos Rivados são verdadeiras?";
			link.l1 = "Exatamente! E não há histórias. Eu conheço mais dois ídolos no arquipélago que teleportam quem os toca de um para o outro, em círculo.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Entendo, entendo. Vou ter que confiar em você, embora suas palavras sejam um absurdo anticientífico. Teleportes, estátuas... ha! Quem poderia imaginar, como essas coisas funcionam afinal?";
			link.l1 = "Confie em mim e não tente encontrar lógica nisso. Não estou mentindo.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Certo. Mas espero que você não tenha perdido o traje durante essa sua teletransporte?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Claro, não fiz isso. De certa forma, isso me salvou dos Caribes. Aqui está.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Claro, não foi bem assim. De certo modo, ela me salvou dos caribes. Mas agora não estou com ela.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Então traga isso pra mim, droga! Não vamos conversar até você me devolver, entendeu?";
			link.l1 = "Calma, Mecânico. Eu vou devolver pra você!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ah, você realmente trouxe meu traje! Obrigado, já estava começando a me preocupar com isso.";
				link.l1 = "Não precisava se preocupar com isso. Eu te prometi que devolveria.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Nem venha aqui até trazer meu traje.";
				link.l1 = "Tudo bem, tudo bem.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Muito bom. Eu já estava pensando em fazer outro, mas isso levaria pelo menos um ano... Fico feliz que você tenha tido bom senso e devolvido minha propriedade inteira. Vou até te dar um presente.";
			link.l1 = "Você está falando sério?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Claro que sim! Você me ajudou a consertar o traje e não o jogou fora na primeira oportunidade. Você cuidou dele e, finalmente, trouxe de volta para mim. De qualquer forma, aqui está uma ótima caixa de ferramentas. Aprenda a usá-la. Com ela, você vai conseguir fazer muitas coisas úteis.";
			link.l1 = "E o que mais eu poderia esperar do Mecânico! Claro, a caixa de ferramentas! Obrigado, Henrik, estou comovido... Eu não merecia um presente desses.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eu sei melhor do que ninguém o que você mereceu e o que não mereceu. Pegue! Vai ser útil pra você. Mas só devolvo o traje se você deixar 500.000 pesos de garantia, por causa desse seu costume de sumir pelos ídolos.";
			link.l1 = "Caramba! Bem, eu entendo... medidas de precaução...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Claro. E se um dia você fugir com isso? Então o dinheiro será minha compensação.";
			link.l1 = "Tudo bem, Henrick. Eu concordo. Para ser sincero, achei que você nunca mais fosse me dar isso.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Nem pensar. Prometa meio milhão e é tudo seu.";
			link.l1 = "Fechado! Posso pegar como sempre pra mergulhar então? A partir de amanhã?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Exatamente.";
			link.l1 = "Obrigado! Até mais, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você está fazendo aí, hein? Ladrão!","Olha só! Mal me perdi em pensamentos, você já foi mexer no meu baú!","Veio fuçar nos meus baús? Não vai sair impune!");
			link.l1 = "Maldição!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Veio mexer nos meus baús? Você não vai sair impune disso!";
			link.l1 = "Garota tola!...";
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
			link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, sou cidadão desta cidade e peço que guarde sua espada.","Escute, eu sou um cidadão desta cidade e gostaria que você guardasse sua espada");
				link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, camarada, andando por aí com uma arma. Posso ficar nervoso...","Não gosto quando as pessoas passam na minha frente com as armas na mão. Isso me assusta...");
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
