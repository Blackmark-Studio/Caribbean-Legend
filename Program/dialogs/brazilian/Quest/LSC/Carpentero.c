// Санчо Карпентеро - бармен
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
				dialog.text = "Fora daqui! Eu não vou servir canalhas que atacam pessoas inocentes nas ruas!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! Que bom te ver, por Deus! Eu sabia – eu sabia! – que os boatos não eram verdadeiros! Droga, toma um drink comigo!";
				link.l1 = "Vamos beber, Sancho! Também estou muito feliz em te ver!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", sinto muito que você tenha perdido. Poucos conseguem beber mais do que aquele gordo. Como está sua cabeça?";
				link.l1 = "Você... você serve um rum forte pra caramba, Sancho. Te devo pelas bebidas... quanto é?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Você venceu o Fazio, "+pchar.name+"! Estou pasmo! Só um ou dois conseguiram beber mais do que ele. Aqui, pegue suas duzentas dobrões.";
				link.l1 = "Obrigado pelas palavras gentis, Sancho!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? Dizem que você mergulhou até o fundo usando um traje feito por aquele mecânico Narval. É verdade?";
				link.l1 = "É verdade, camarada. Eu já vi o fundo do mar!";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Saudações! Sempre fico feliz em ver um rosto novo na minha taverna! Seja bem-vindo! Aqui você sempre vai encontrar uma boa bebida – estamos até a borda com vinho europeu!\nJá não posso dizer o mesmo da comida, viu. Ha... brincadeira. Meu nome é Sancho Carpentero, este é o meu lugar.";
				link.l1 = TimeGreeting()+", Sancho. Meu nome é "+GetFullName(pchar)+". Prazer em conhecê-lo.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, meu amigo "+pchar.name+"! Que bom te ver! O que vai querer?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Escuta, Sancho, você sabe onde posso conseguir um bom rifle? Não um mosquete comum de infantaria, mas algo preciso e de longo alcance – talvez para caçar.";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Escute, Sancho, tenho algumas perguntas para você. Estou procurando um homem chamado Adolf Barbier. Ouvi dizer que ele costuma beber aqui...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Escuta, Sancho, dizem que o Chad Kapper comprou arsênico de você...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, quero te mostrar uma coisa. Essa é a máscara de morcego que você estava tentando conseguir?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, vim buscar minha couraça. Aqui está o dinheiro.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, vim buscar minha couraça. Aqui está o dinheiro.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Me sirva um pouco de rum, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Quero alugar um quarto.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Estou entediado, Sancho. Quero passar um tempo aqui com uma garrafa de vinho até o anoitecer...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Sobre o que as pessoas andam conversando hoje em dia, Sancho?","O que tem acontecido na ilha ultimamente?","Alguma novidade?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Tenho garras de caranguejo para te vender, Sancho.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, quero te perguntar uma coisa sobre a ilha.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "Não, camarada. Só queria saber como você está. Tchau!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Eu também. Espero te ver pelo menos uma vez por noite, ha-ha! Fico sinceramente feliz em receber um novo visitante na minha taverna.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Me sirva um pouco de rum, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Quero alugar um quarto.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, quero te perguntar uma coisa sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "Até mais, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "Não, amigo, não posso te ajudar. Minha especialidade é cerveja e vinho, não mosquetes, ha-ha! Vá até a loja, ouvi dizer que o Axel às vezes vende armas interessantes. Talvez você encontre o que procura por lá.";
			link.l1 = "Obrigado pelo conselho.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf? Sim, ele me visita de vez em quando, mas já faz alguns dias que não o vejo. Ele está desaparecido desde que conversou com aquele homem gordo, o Giuseppe.";
			link.l1 = "Giuseppe... você quer dizer Giuseppe Fazio?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Só tem um Giuseppe na ilha. É, é ele mesmo. Eles ficaram sentados por algumas horas, dividiram uma garrafa de rum e tiveram uma conversa bem animada.";
			link.l1 = "Eles estavam discutindo?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Não. Eles conversaram como velhos amigos. Olha, só vai falar com o Fazio no Caroline e pergunta pra ele.";
			link.l1 = "Certo, eu faço isso.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "Só isso? Você disse que tinha algumas perguntas...";
			link.l1 = "Sim. Me diga, quem são a Mary Vermelha e o Marcello Ciclope?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Red Mary is one of the Narwhals. Beautiful young girl, but absolutely wild. She wields her blade and a handgun as good as any man. Used to be the girlfriend of Alan Milrow, a former leader of the Narwhal clan, before the Admiral killed him\nAlan's death hit her hard. She spends her days crying and cursing Shark in her cabin on the Ceres... But she will get over it; life goes on, after all.\nI don't know much about Marcello, only seen him a couple of times. Scary fellow. They say he used to be a royal hunter, lost an eye in a fight, and went sailing on a merchantman as a mercenary - spent his days at sea repelling hostile boarding actions.\nUnsurprisingly... he hates pirates.";
			link.l1 = "Entendi... Muito obrigado, Sancho, você foi de grande ajuda.";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "De nada, amigo. Volte aqui outra hora, e vamos tomar uma cerveja juntos.";
			link.l1 = "Claro!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapper? Não. Ele não apareceu na taverna recentemente. Marcello Ciclope comprou um frasco de arsênico faz só uns quinze minutos – acho que ele também está com problemas de ratos. Eu entendo perfeitamente... malditos ratos.";
			link.l1 = "O Ciclope esteve aqui?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Bem, sim. Por quê?";
			link.l1 = "Estou procurando por ele há alguns dias. Você sabe para onde ele foi?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ele estava na companhia de Adolf Barbier, que mora na Santa Florentina. Talvez tenham ido para lá?";
			link.l1 = "Obrigado!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Se você precisar de arsênico, posso vender um frasco por vinte doblões--!";
			link.l1 = "Depois a gente conversa sobre isso, Sancho, tchau!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Vamos lá, amigo, você não me deve nada.  Já perdeu cem dobrões. É isso que acontece quando tenta beber mais que o Fazio...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Não, não, Sancho, por favor! Fique com esses quinhentos pesos. Isso deve cobrir o valor das bebidas, pelo que me lembro. Não quero ficar te devendo.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "É... obrigado, Sancho. Você tem razão.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm... então tenho uma proposta pra você. Viu algum caranguejo gigante lá embaixo?";
			link.l1 = "Você está brincando? Eram hordas deles! O que você tinha em mente?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Se você matar algum deles, traga as garras para mim. Vou te pagar bem em dobrões: cinco moedas por cada uma! Axel Yost não vai pagar tanto, pode ter certeza.   Não estou pedindo para você sair caçando... mas se acabar matando um ou dois, lembre-se da minha oferta...";
			link.l1 = "Por que as garras? E as outras partes do caranguejo?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Porque a maior parte da carne está nas garras. Os caranguejos não têm muita carne nas pernas e seus corpos são cobertos por uma carapaça dura. A carne de caranguejo é uma iguaria por aqui. Tem um sabor requintado e é muito nutritiva!\nTenho uma receita especial para ela, então vou te pagar cinco dobrões por cada garra.";
			link.l1 = "Certo, vou lembrar disso...";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Excelente! Quantos você tem?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "Mudei de ideia.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "Certo. Aqui, pegue seus dobrões - "+FindRussianQtyString(iTotalTemp*5)+". Valeu, camarada, se conseguir mais, traga pra mim.";
			link.l1 = "Claro, amigo.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "O quê?! Mostre-me! Deixe-me ver!";
			link.l1 = "Tá bom, tá bom, ha-ha!";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Isto... isto é isso! É exatamente igual ao que está no desenho que o marinheiro fez pra mim!\nAmigo... você me venderia isso?";
			link.l1 = "Depende. Se bem me lembro, você prometeu uma fortuna de rei por isso.";
			link.l1.go = "rat_2";
			link.l2 = "Desculpe, amigo, não está à venda. Preciso disso para o meu navio. Só queria que você confirmasse se este é mesmo o talismã de que você estava falando.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, que pena... Sim, meu amigo, esse é o talismã. Sortudo! Agora você nunca mais vai precisar se preocupar com ratos! E eu vou ter que continuar exterminando eles com arsênico...";
			link.l1 = "Me desculpe por ter te dado falsas esperanças, Sancho. Eu não tinha certeza de como era essa coisa, então precisei confirmar. Me desculpe.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "Para isso,"+pchar.name+", eu... eu vou lhe oferecer a chance de comprar o item mais valioso e precioso que possuo! Deixe-me buscá-lo para você...\nDê uma olhada. Aqui está uma Couraça de Milano única e deslumbrante, feita com maestria! Ela oferece proteção excepcional em combate, permite total liberdade de movimento e é leve e confortável. Uma armadura dessa qualidade é extremamente rara, tanto no Caribe quanto na Europa.\nEncontrei essa couraça nos aposentos do capitão de um navio de guerra espanhol há alguns anos e a guardei justamente para uma ocasião como esta. Estou disposto a vendê-la a você por duas mil moedas de ouro mais o Deus Rato!";
			link.l1 = "Hmm... Ora, esta é realmente uma couraça de mestre! Acho que essa troca me cai bem. Existem muitas maneiras de lidar com ratos, mas encontrar outra couraça como esta seria quase impossível. Nunca vi uma igual antes. De fato, é uma peça única de armadura.";
			link.l1.go = "rat_yes";
			link.l2 = "Quanto?! Sancho, seus ratos já te morderam hoje de manhã? Como assim, dois mil? Você faz ideia do que eu passei pra encontrar esse ídolo?! Baixa esse preço agora!";
			link.l2.go = "rat_torg";
			link.l3 = "Quanto?! Você é um agiota, sabia disso, Sancho? 'Oferecer a chance de comprar' – ha! Por esse preço, eu poderia encomendar uma armadura no continente que desviaria balas e me deixaria andar sobre a água! E pra que você precisa de tanto ouro, pra mandar o Jurgen fazer uma estátua sua e exibir no convés do San Agustine?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "Fico feliz que você esteja a bordo, meu amigo. Obrigado por não esquecer do meu problema! Então, vou esperar meus dobrões. A armadura vai estar te esperando!";
			link.l1 = "Vou trazê-los em breve!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", under different circumstances, I would demand five thousand. The Admiral himself has shown interest - and he is not the only one, believe me. But take your time deciding; the armor will be waiting for you for as long as you need. I'll only sell it to you.";
				link.l1 = "Vou pensar nisso, Sancho.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", em outras circunstâncias, eu pediria cinco mil. O próprio Almirante demonstrou interesse — e acredite, ele não é o único.\nTudo bem, vou tirar quinhentos, já que você não se esqueceu de mim e do meu problema. Deve ter sido uma aventura e tanto.";
				link.l1 = "Assim está melhor... mas ainda não entendo por que eu deveria pagar a mais nessa troca de itens tão únicos quanto os seus. Talvez você é que devesse me pagar, hein Sancho, he-he?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "Não, "+pchar.name+", nem pensar. Eu até dou um jeito em ratos com arsênico, mas essa armadura pode salvar sua vida um dia. E você vai parecer um duque italiano usando ela! Mil e quinhentos, é minha última oferta. Pense com calma e me avise. A armadura vai te esperar o tempo que precisar, só vou vender pra você.";
				link.l1 = "Sancho, se você não fosse o único dono de taverna nesse cemitério sombrio... Vou pensar na sua proposta.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "Para um capitão militar e pirata, você realmente sabe negociar! Lembra do Jost? Uma vez ele conseguiu comprar todo o meu arsênico por um preço baixo, enquanto os ratos já estavam me atormentando.\nTudo bem, "+pchar.name+", você venceu. Vou tirar mais quinhentos pra você! Mas essa é minha oferta final!";
				link.l1 = "Isso ainda parece uma exploração, mas pelo menos agora não vou me sentir como uma donzela indefesa na selva. Espere por mim, vou trazer o dinheiro em breve.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Calma, "+pchar.name+". De qualquer outra pessoa, eu pediria cinco mil! O próprio Almirante demonstrou interesse — e acredite, ele não é o único.\nA armadura vai estar te esperando — não vou vendê-la para mais ninguém por enquanto.";
			link.l1 = "Que honra! Eu volto já. Dois mil!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Pronto! Que bom que concorda, amigo. Obrigado por não esquecer do meu problema! Pegue a couraça, e que ela te proteja bem nas batalhas.";
			link.l1 = "Aqui, pegue seu talismã – parece que dias sombrios estão chegando para os ratos da sua taverna, ha-ha!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "Você ainda me impressiona "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "Nem me lembre disso!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Estou ouvindo, amigo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "O que é esta ilha? Pode me contar mais sobre ela?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Como eu sairia da ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "O que devo saber sobre a ilha?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "E como você está aqui? E a sua taverna?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Não tenho perguntas, deixa pra lá...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "This island? Well, they call it Justice Island, the Island of Justice, or the City of Abandoned Ships - but we just call it the island. It's formed out of shipswrecks, which are stuck on a shoal at the centre of the reefs.\nThis central part of the island is our living space; the outer ring of wrecks is uninhabited. There's been no connection with the outside world for ten years.";
			link.l1 = "Incrível!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Construa um barco longo ou uma jangada – mas isso não vai acabar bem pra você. Tempestades e correntes fortes cercam a ilha, e se você passar do anel externo, estará arriscando a própria vida. Você precisaria de uma equipe de marinheiros de primeira pra ter alguma chance de sobreviver, e poucos daqui estão dispostos a deixar este lugar. Menos ainda querem arriscar ir além do anel externo. O pessoal gosta de viver aqui. Pergunte por aí se não acredita em mim.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Primeiro, você deve lembrar que existem várias áreas restritas na ilha. Dois clãs, os Narvais e os Rivados, vivem aqui há muito tempo, lutando entre si sem parar e protegendo os territórios que consideram seus. Se aparecer sem ser convidado, está perdido.\nVocê precisa saber a senha atual se quiser entrar no território deles. Não se preocupe em invadir sem querer, os guardas vão te avisar várias vezes antes de começarem a atirar.";
			link.l1 = "Vou me lembrar disso...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "You know, my friend, it's fine. I'm used to working with food and drink. I served as a cook lots of places in Europe - garrisons, grog houses, ships - so the first thing I did here was establish a tavern.\nI like my job and my life is satisfying. Everybody needs food and drink, and I enjoy serving them. Folks are friendly, here, and mostly peaceful. I can't remember the last time I had to clean up after a drunken brawl. And the clans don't bother me.\nAll in all, this the best place I've had in my life. I'm free here, and no one tells me what to do.\nThe only thing driving me mad is the rats. They torture me; eating my provisions and ruining my tableware. And they're impossible to get rid of.";
			link.l1 = "Ah, sim, eu sei muito bem como esses pestinhas podem ser problemáticos...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Seems I'm the most unfortunate person in the city when it comes up to rats. Other ships are not terrorized nearly as badly as my Fleuron. Axel Yost somehow managed to get rid of his rats once and for all, but me, I've got armies of the furry bastards crawling around.\nYou know, I once heard tell of a special amulet called the Rat God. It looks like a bat's face. Supposedly this amulet scares rats away completely.\nMust be how Axel dealt with his rats; he buys and re-sells every piece of garbage people bring him from the outer ring.\nIf someone offered me that amulet, I'd pay a king's ransom for it!";
			link.l1 = "Vou me lembrar disso...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", Acho que você já bebeu demais, amigo. Deus me livre de você ser roubado ou cair no mar para servir de comida aos caranguejos. Não é uma boa ideia beber demais por aqui, isso pode te matar.";
				link.l1 = "Hm... Suponho que você tem razão, Sancho – hic! – já bebi o bastante. Obrigado pela preocupação.";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "De nada, camarada. Só vinte e cinco pesos por uma caneca do meu melhor rum!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("À sua saúde e à prosperidade da sua taverna, amigo!","A todos os filhos do mar, onde quer que estejam!","Ao povo da Ilha da Justiça!"),LinkRandPhrase("À ilha, e que ela dure para sempre!","Que o vento esteja sempre a nosso favor, seja qual for o rumo que tomarmos!","À sorte, à felicidade... e às mulheres!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Acho que você não devia beber agora. Confie em mim...";
				link.l1 = "Tudo bem...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Heh, você é um sujeito estranho... Não tem ninguém pra passar o tempo aqui na ilha? A Mary vai me matar se eu deixar você ficar aqui bebendo sozinho. Volte aqui à noite com alguém e aproveite até o amanhecer, se quiser.";
				link.l1 = "Boa ideia!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Sem problema, camarada. Por apenas trezentos pesos você leva uma bela garrafa de "+LinkRandPhrase("Spanish","Italian","Francês")+" vinho - e uma mesa pelo tempo que quiser.";
				link.l1 = "Obrigado!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Acho que você não deveria dormir agora. Confie em mim...";
				link.l1 = "Tudo bem.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Não consigo te entender, camarada. Tem uma moça linda te esperando no Ceres e você quer passar a noite sozinho na taverna? Não posso deixar, a Mary me mataria.";
					link.l1 = "Provavelmente você está certo...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "You can rest upstairs until the evening, but I won't let you spend the night here; Mary would kill me. Sorry...";
					link.l1 = "Tudo bem, vou ficar aqui até o anoitecer...";
					link.l1.go = "hall_night_wait";
					link.l2 = "Tudo bem... Eu me viro sem dormir.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Por vinte pesos, você pode dormir na cama lá em cima. Quando devo te acordar?";
			if(!isDay())
			{
				link.l1 = "De manhã.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Antes do anoitecer.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Na manhã seguinte.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Mudei de ideia. Não quero dormir.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
