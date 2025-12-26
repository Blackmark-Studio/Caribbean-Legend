int iFadeyPseudoGlobal;

// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> LoyaltyPack
			if (GetDLCenabled(DLC_APPID_1))
			{
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "ready"))
				{
					link.l32 = "Fadey, você conhece um homem chamado Alonso?";
					link.l32.go = "LoyaltyPack_Fadey_1";
				}
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "money") && PCharDublonsTotal() >= 1000)
				{
					link.l32 = "Fadey, estou pronto para comprar sua couraça de espelho.";
					link.l32.go = "LoyaltyPack_Fadey_1000";
				}
			}
			//<-- LoyaltyPack
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "O que posso fazer por você, Monsieur? Não converso com desconhecidos. Se veio só bater papo ou perguntar quando o Comboio de Prata espanhol chega a Maracaibo em 1640, sinto muito, mas vou decepcioná-lo. Não perco meu tempo com conversa fiada.";
					link.l1 = "Boa tarde, Monsieur Fadey. Talvez ainda não me conheça, mas certamente conhece meu irmão. Permita-me apresentar: Charles de Maure, irmão de Michel de Monper.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Aha, você de novo, Charles! Kak dela? O que foi agora?";
					link.l1 = "Você disse que foi roubado... Já encontrou os culpados?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "Então, Charles, você já foi falar com aquele selvagem?";
					link.l1 = "Eu tenho... É por isso que voltei para você.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ah, é você de novo, meu caro amigo! Então, trouxe o resgate em dobrões para o índio?";
					if (CheckAttribute(npchar, "questTemp.Sharlie.Tichingitu_Skidka"))
					{
						if (PCharDublonsTotal() >= 35) // belamour legendary edition
						{
							link.l1 = "Sim. Aqui estão seus 35 dobrões.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Não, ainda não consegui juntar o suficiente.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 40) // belamour legendary edition
						{
							link.l1 = "Sim. Aqui estão seus 40 dobrões.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Não, ainda não consegui juntar o suficiente.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, ora, é o próprio Monsieur de Maure! Eu disse pra entrar, não fique aí parado! O que te traz ao meu domicílio?";
					link.l1 = TimeGreeting()+", Fadey, meu irmão me disse para procurar você. Ele falou que você poderia me ajudar a encontrar algum trabalho.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, é você! O que te traz aqui, Monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. Meu irmão insistiu para que eu não falasse com você sobre isso, mas eu não consegui me afastar... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Ah, velho amigo! Entre, entre, "+pchar.name+"! Como vai você?";
					link.l1 = TimeGreeting()+", Fadey. Que bom te ver. Na verdade, tenho um assunto importante pra tratar. Ouro negro.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Ah, é você de novo, meu caro amigo! Conseguiu o saque? Encontrou dobrões suficientes?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Sim, Monsieur Fadey! Aqui está o seu ouro.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "Não, só estou de passagem. Ainda estou procurando a quantia certa.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, acabei de ter uma ideia. Não preciso mais dos escravos. Com licença, nos vemos depois!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Ah, meu velho amigo! Entre, entre, "+pchar.name+"! Como vai você?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", preciso da sua ajuda de novo.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Que bom te ver. Tenho negócios para tratar com você.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, é você de novo, meu caro amigo! E então, conseguiu o dinheiro?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "Eu trouxe, Monsieur Fadey! Aqui estão seus 75 doblões.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Eu trouxe, Monsieur Fadey! Aqui estão seus 40.000 pesos.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "Não, só estou de passagem. Ainda estou procurando a quantia certa.";
						link.l3.go = "exit";
					}
					link.l4 = "Com licença, Fadey, mas não posso pagar por isso. Vou tentar me virar sozinho. Até mais!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Entre, entre, "+pchar.name+"! Consigo ver nos seus olhos que você quer ouvir sobre o meu sucesso.";
					link.l1 = "Exatamente, Fadey. Confio que você trouxe o que eu quero.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, é você de novo, meu caro amigo! E então, conseguiu o dinheiro?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "Pegue 75 doblões. Vou pedir aos marinheiros para levarem esta caixa até o meu navio. Ah, o que seria de mim sem você, Fadey?! Você não faz ideia do quanto me ajudou!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Pegue 40.000 pesos. Vou pedir aos marinheiros para levar esta caixa até o meu navio. Ah, o que eu faria sem você, Fadey?! Você não faz ideia do quanto me ajudou!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "Não, só estou de passagem. Ainda estou tentando juntar o suficiente.";
						link.l3.go = "exit";
					}
					link.l4 = "Excuse me, Fadey, I'm completely broke. Keep the deposit; I hope it will be enough to cover your expenses for this deal, and I'll try to manage on my own. See you!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				//--> Дикая Роза
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey"))
				{
					dialog.text = "Ah, aqui está você, meu caro! Quando soube que seu navio havia ancorado em nosso porto, fiquei na esperança de que viesse me visitar.";
					link.l1 = "Olá, "+npchar.name+". Não vou te cansar com uma longa história. Minha companheira Mary e eu estamos procurando o pai dela, que desapareceu sem deixar rastros há vinte anos...";
					link.l1.go = "WildRose_Fadey_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2")) 
				{
					link.l31 = "Quanto ao pai da Mary...";
					link.l31.go = "WildRose_Fadey_return";
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3"))
				{
					dialog.text = "Ora, veja só quem apareceu, "+pchar.name+"!";
					link.l1 = "Você está radiante, "+npchar.name+". Então, me diga—conseguiu descobrir alguma coisa?";
					link.l1.go = "WildRose_Fadey_16";
					break;
				}
				//<-- Дикая Роза
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ah, Marcado—digo "+pchar.name+"! Vamos lá, me conta o que você tem pra mim!";
					link.l1 = TimeGreeting()+", Fadey. Prazer em te ver. Vim falar com você sobre negócios.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Aposto que você está curioso para saber o resultado da minha conversa de autodescoberta com o padre.";
					link.l1 = "Claro que estou! Como foi?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ah, me perdoe, estou tão distraído pelo tilintar nos seus bolsos!";
					link.l1 = "Quanta ganância, Fadey! Aqui está o seu ouro.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Aha, meu velho amigo! Entre, entre, "+pchar.name+"! Então, tem alguma novidade?";
					link.l1 = "Olá, Fadey. Mais uma vez venho pedir seu apoio.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "O que foi, virou estátua? Se tem algo pra dizer, fala logo. Se não, cai fora. "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Dá uma olhada, Fadey. Suponho que isso seja um shamshir persa, talvez um daqueles roubados da sua coleção?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "Tenho boas notícias para você. Tenho outro shamshir persa para você aqui.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "Tenho um terceiro shamshir persa. Assim como você pediu, trouxe de volta assim que pude.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "Vim falar sobre a armadura leve que combinamos.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, eu gostaria de comprar um pouco da sua famosa corda.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, preciso da sua ajuda.";
				link.l1.go = "help";
 				link.l9 = "Não, nada no momento.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Em que posso ajudá-lo, Monsieur? Não falo com pessoas que não conheço.";
				link.l1 = "Ah, só passei para ver quem mora aqui.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Ah, então você é o irmão caçula do bom e velho Michel! Isso muda tudo! Entre, entre, Monsieur, sente-se. Aceita brindar com um copo de vodca ao nosso encontro? Ainda tenho algumas garrafas, e seria um prazer dividir uma com o irmão de um grande amigo, da!";
			link.l1 = "Perdoe-me, Monsieur Fadey, mas beber não está nos meus planos esta noite. Prefiro ir direto ao assunto.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "O que você está dizendo! Este rum local é uma água suja fraca comparada à vodca russa! Você não faz ideia do que está perdendo, que o Mar me leve se eu estiver mentindo! Muito bem, vamos aos negócios então. Estou todo ouvidos, Charles.";
			link.l1 = "Monsieur, receio que o que estou prestes a lhe dizer será bastante desagradável, mas, infelizmente, meu dever me obriga a fazê-lo! Michel me contou que o senhor lhe deve uma quantia considerável por causa de jogos de azar com ele. Ele também pediu que o dinheiro fosse entregue a mim, pois meu irmão está... impossibilitado de vê-lo pessoalmente neste momento.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Oh, rapaz! Claro que me lembro de tudo e admito que devo ao seu irmão. Dívida de jogo é sagrada, cumprir com essa obrigação é o que nos salva da anarquia mortal e de bandidos perigosos! Mas, por favor, peço que entenda minha situação! Aconteceu comigo uma história bem desagradável recentemente – fui roubado de forma descarada!\nMalditos ladrões levaram tudo o que puderam, tudo o que conquistei em anos de trabalho, meu dinheiro e minha coleção inestimável! Simplesmente não tenho como quitar a dívida agora, não dá\nMas, Monsieur de Maure, não fujo das minhas obrigações! Só peço que me encontre no meio do caminho. Já que não tenho nenhuma moeda comigo no momento, ofereço este excelente punhal raro. Veja só!\nÉ uma verdadeira obra-prima de aço, o orgulho da minha coleção roubada. Além disso, foi encantado por xamãs indígenas e possui poderes ocultos muito fortes! Os índios o chamavam de Garra do Chefe\nJamais teria concordado em me desfazer dele, pois paguei uma fortuna por esse punhal, muito mais do que a dívida, mas considerando as circunstâncias e minha relação com seu irmão mais velho, estou pronto para lhe entregar. Fique com ele, é um ótimo negócio!";
			link.l1 = "Eu prefiro muito mais o dinheiro do que uma faca...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "Mas eu não tenho o dinheiro e tenho este raro artefato encantado! Você realmente acha, drug moy, que eu te ofereceria essa magnífica adaga mágica em vez de algumas moedas de prata sem valor em outras circunstâncias? Pesos você acha em qualquer lugar, até jogados na rua! Admita, estou numa situação complicada aqui. Meu coração sangra só de pensar em me desfazer dessa peça incrível de artesanato, mas dívida de jogo é dívida de honra, então estou disposto a te dar só a você, embora me seja muito preciosa, porque você é um verdadeiro homem de honra e um verdadeiro amigo.";
			link.l1 = "Certo, já que você jura que não tem dinheiro, vou ficar com essa sua adaga mágica. Tomara que eu consiga vendê-la por um bom preço...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Vender isso'!? Cai fora daqui, stal- digo, Charles! Não, mal posso acreditar no que estou ouvindo! Estou te dando meu bem mais precioso, pelo qual eu conseguiria pelo menos dez vezes mais lá na Europa, e você fica aí, com essa cara de pau, dizendo que vai simplesmente penhorar!? Ora, esse punhal, rapaz, salvou a vida de um homem! Deixa eu te contar—";
			link.l1 = "E que poder oculto é esse que você mencionou?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, ho ho! Agora, Charles, eu sou um bom cristão, sabe, não algum xamã indígena. Não tenho como saber todas as propriedades ocultas desta lâmina. Mas elas existem, ah, existem sim! Segure este punhal na mão e você mesmo vai sentir o poder que ele tem! Pegue, pegue! E então? Sente alguma coisa?";
			link.l1 = "Hm... Não sinto nada. Mas ela encaixa bem na minha mão.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Ah ha! Aí está! Mas isso é só o menor dos seus atributos. Se você empunhar essa adaga em combate, tenho certeza de que ela vai mostrar seu poder de maneiras bem impressionantes! Então, vai levar?";
			link.l1 = "Bem, eu tenho escolha? Vou aceitar, já que você não tem dinheiro...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Obrigado, Charles. Você não vai se arrepender, pode ter certeza! Aqui está. E não esqueça de mandar um abraço para o Michel por mim! Diga para ele aparecer quando puder.";
			link.l1 = "Ah, eu vou contar pra ele...";
			link.l1.go = "exit";
			link.l2 = "Você disse que tinha sido roubado... Já encontrou os culpados?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "The problem is, I haven't. Those ruffians cleared out the whole house, ran off with all the silver, gold, my savings from years of back-breaking labour. Now, that usually doesn't bother me; after all, a real gentleman, even if he loses everything he owns, must show no emotion! Money must be so far beneath a gentleman that it is hardly worth troubling about. But the worst part is, they swooped up my magnificent collection of Persian shamshirs! There isn't a collection like it in all of the New or Old World combined. Truly remarkable Persian cavalry swords...";
			link.l1 = "Espadas persas, é isso? Isso soa bem interessante. Então, você é um colecionador, não é?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Bem, eu gosto de colecionar coisas raras... Escuta, Charles, talvez você possa me ajudar com isso...";
			link.l1 = "Ajuda? Mas como? Você quer dizer pegando os ladrões?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Não. Não estou particularmente interessado nos ladrões. Gostaria mesmo é de ter minhas cimitarras persas de volta. Se você encontrá-las, garanto que vou recompensar muito bem, prometo.";
			link.l1 = "Hm. Mas onde eu deveria procurá-los? Pelo Caribe? Ou talvez pelo mundo todo?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Well, perhaps you'll catch sight of them on the islands at some street merchants; those scoundrels can't even comprehend the value of those cavalry swords, and they'll surely sell them for scraps. So if you see the Persian swords anywhere, bring them to me. Will you be able to recognise them?";
			link.l1 = "Acho que vou sim. Certo, vou ficar de olho, e se eu vir alguma lâmina incomum que bata com a descrição, com certeza trago pra você.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Sabe, eu não sou especialista em armas finas. Receio que não vou conseguir te ajudar. Seria desonesto da minha parte te dar falsas esperanças.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Horosho! Espero que você tenha sorte e encontre esses artefatos, e eu vou recompensar você por isso. Boa caçada, caçador— quer dizer, capitão! Da, Charles, você acredita que tentaram me roubar de novo recentemente?\nUm ladrão tentou invadir minha casa há poucos dias\nDessa vez foi demais pra mim! Mas ele não escapou de mim, consegui pegá-lo, dei uma boa surra nele e entreguei para os guardas da prisão da cidade. Espero que enforquem esse desgraçado logo!";
			link.l1 = "Você acha que ele é um dos ladrões que roubaram seus shamshirs?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Que pena, mas não adianta chorar pelo leite derramado. Sim, Charles, acredita que outro dia tentaram me assaltar de novo?\nUm ladrão tentou invadir minha casa há poucos dias\nIsso foi demais pra mim! Mas ele não escapou: consegui pegá-lo, dei uma boa surra e mandei direto pra cadeia. Não se pode ser feliz às custas da desgraça alheia. Espero que enforquem esse miserável logo!";
			link.l1 = "Você acha que ele é um dos ladrões que roubou seus shamshirs?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Não, acho que não. Ele estava atrás de dinheiro. Peguei ele no meu quarto, revirando meus baús\nUm índio de alguma selva remota do continente espanhol. Ele parece ridículo, bem diferente dos que vivem por aqui. Todo coberto de pintura de guerra e vestido com uma fantasia colorida... Você devia ir até a masmorra ver esse bobo com seus próprios olhos, se quiser, enquanto ele ainda está vivo.";
			link.l1 = "Hm... Talvez eu passe lá para vê-lo.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Vai lá, dá uma olhada nesse show de horrores... Horosho, Charles, foi bom conversar com você. Boa viagem de volta à Martinica, poputniy veter!";
			link.l1 = "Tudo de bom, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("Tichingitu_SetTichingituJail");
			SetFunctionTimerCondition("Tichingitu_FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Que interessante! Estou ouvindo.";
			link.l1 = "Fadey, falei com aquele índio. E vim te pedir ajuda para tirá-lo de lá. O coitado só queria algo para comer...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, e você acreditou nessa história? Os jovens de hoje são tão ingênuos...";
			link.l1 = "Fadey, eu posso ser mais jovem que você, mas até eu sei quando estão me dizendo a verdade e quando estão mentindo. Além disso, você realmente acha que enforcamento é um castigo justo pra esse tipo de crime? Parece exagero. Lá em casa, no máximo, o sujeito levaria umas chibatadas ou seria marcado a ferro se fosse reincidente.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Excessivo!? Ele invadiu minha casa! Esse selvagem nunca deveria ter vindo aqui! O que você faria se estivesse no meu lugar? Aposto que transformaria as tripas dele em comida de verme, não é?!";
			link.l1 = "Não, eu não faria isso, Fadey. Você ainda está irritado por causa da sua coleção de shamshirs roubada. Se isso não tivesse acontecido, você estaria mais disposto a dar uma boa surra nesse índio bobo e um chute no traseiro dele, estou errado?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles... Você é igualzinho ao seu irmão... Horosho. Vamos resolver isso como homens de negócios honestos. Já que você quer tanto esse índio, me compense pelo prejuízo moral e pelos danos materiais que ele causou e, em troca, direi ao comandante que não quero prestar queixa. O que acha?";
			link.l1 = "Quanto?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, você já está começando a aprender os costumes do Caribe, Charles. Cento e cinquenta dobrões de ouro, nem um tostão a menos.";
			link.l1 = "Fadey, que Deus tenha piedade...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Tá bom, tá bom, 40 dobrões de ouro. Mas esse é o preço final. E dobrões, não pesos. Nosso agiota com certeza vai ter alguns.";
			if(PCharDublonsTotal() >= 40) // belamour legendary edition
			{
				link.l1 = "Eu tenho o valor necessário agora. Aqui, pegue seus 40 dobrões.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Confiável) Fadey, escuta... Eu entendo a sua frustração, mas sou o único disposto a te compensar com dinheiro de verdade por esse transtorno.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "Certo, vou buscar o que você precisa.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Ah, você vai longe, meu amigo. Você me convenceu! 35 moedas de ouro — nem uma a menos!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			npchar.questTemp.Sharlie.Tichingitu_Skidka = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "E apresse-se, Charles! Você tem apenas dez dias até que ele seja executado.";
			link.l1 = "Vou me lembrar disso. Adeus!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka"))
			{
				RemoveDublonsFromPCharTotal(35);
				DeleteAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka");
			}
			else RemoveDublonsFromPCharTotal(40); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Muito bem. Vou escrever uma nota agora mesmo e colocar meu selo, espere um instante... pronto. Entregue isso ao comandante e pode levar seu índio com você. Não sei por que exatamente você se preocupa tanto com ele, mas isso é problema seu. O que vai fazer, exibi-lo num baile de máscaras? Haha, essa é boa!";
			link.l1 = "Deus vê tudo, Fadey. Salvar a vida de um homem é um ato nobre.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "Concordo com a sua primeira afirmação, mas a segunda é discutível, Charles. E se você salvar um assassino ou um estuprador da justiça que o espera no fim de uma corda?  Bah, tanto faz, não é mais problema meu. Que Deus esteja com você. Vá logo falar com o comandante antes que seu amigo de pele vermelha fique pálido com uma corda no pescoço...";
			link.l1 = "Estou indo. Até mais, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Você está com uma cara séria, meu amigo! Imagino que veio me trazer más notícias?";
			link.l1 = "É isso mesmo, Fadey. Vou ser direto com você: o Michel disse que você me enganou com essa história de 'Garra do Chefe'. Ele falou que isso não é artefato nenhum, e que eu poderia comprar igualzinho com qualquer vendedor de rua por algumas centenas de pesos. Fui perguntar pros ambulantes que vendem coisas de metal. Eles me disseram exatamente esse preço.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Oh, Monsieur de Maure... Estou ferido! Seu irmão me surpreende. Esses patetas nas ruas podem falar o que quiserem, mas ele! Me diga, Charles, se alguém trouxesse para você uma velha espada de cavaleiro de duas mãos dos tempos de Carlos Magno e oferecesse para vender, quanto você pagaria por ela?";
			link.l1 = "Uma espada de duas mãos? Você tá de brincadeira comigo agora, Fadey? Pra que diabos eu ia querer uma lâmina enferrujada de carrasco? Estamos no século dezessete de Nosso Senhor Jesus Cristo! Eu não daria nem um mísero peso por isso!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ah, veja só a sua falta de visão, meu amigo! Com essa atitude, você nunca vai chegar a lugar nenhum. E se você trouxesse um artefato desses para mim, eu pagaria trezentos dobrões por ele. Sabe por quê? Porque é uma antiguidade, um tesouro histórico, difícil de encontrar nos dias de hoje! Você não entende, mas já julga! Com Deus e Sua Santa Mãe como minhas testemunhas, a Garra do Chefe é uma adaga magistral—minhas fontes dizem que foi do próprio Cortés. O Hernán Cortés! O lendário conquistador que saqueou Tenochtitlán e capturou o imperador dos astecas! E você debocha e diz que é lixo comum! Além disso, já te falei que não é uma adaga qualquer—é uma adaga encantada! Ainda está tão verde que não viu todas as maravilhas do Caribe? Feitiços e magia, rituais e maldições? Charles, aqui é o Novo Mundo, terra dos maias e astecas, cujo conhecimento dessas artes diabólicas chegou a alturas inimagináveis para nós, cristãos! Essa adaga tem poderes ocultos. Pena que ninguém ainda sabe que tipo de poderes. Você tem uma chance única, incrível, de descobrir por si mesmo do que ela é capaz, e mesmo assim ainda diz que é uma 'porcaria' e que seu pobre e velho amigo Fadey tentou te enganar! Se ao menos eu tivesse dinheiro suficiente para pagar minha dívida com seu irmão, eu trocaria de volta com você na hora, por essas suas moedas desprezíveis... Este é um item muito valioso e seu valor vai muito além do dinheiro, viu?";
			link.l1 = "Tá bom, tá bom, se acalma, Fadey. Eu acredito em você. Seus argumentos são bem convincentes, e o ardor com que você fala é prova da sua sinceridade ou de uma habilidade única pra enganar.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Obrigado! Você agiu bem, Charles, não se ofendendo e vindo direto a mim para pedir uma explicação. Confio que agora a questão está resolvida?";
			link.l1 = "Sim, Monsieur Fadey. Completamente. Agora, por favor, permita-me me retirar...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Pare, Charles! Vou ser sincero, gosto do seu jeito. Quem sabe um dia a gente não vira grandes amigos? E por que não dar o primeiro passo pra essa amizade agora mesmo? Estou gelando duas garrafas de uma excelente vodca russa numa água de nascente lá embaixo, na adega. O que me diz, abrimos uma pra saúde do seu irmão?";
			link.l1 = "Hm. Me desculpe, Monsieur Fadey, mas já está na hora de eu zarpar. Estou com um pouco de pressa.";
			link.l1.go = "vodka_no";
			link.l2 = "Você ofereceu da última vez e eu recusei... Seria indelicado recusar de novo. Tudo bem, Fadey. Tô dentro!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "Que pena. Comparado à vodca, rum é só água, uma coisa fraca e sem graça. Mas já que você está com pressa, não vou te segurar mais. Boa sorte na caçada, Charles!";
			link.l1 = "O mesmo para você, Monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "É disso que eu gosto de ouvir! Excelente! Sente-se e descanse um pouco! Por favor, Monsieur, fique à vontade enquanto eu pego a vodka. Ah, como senti falta dessas tardes com amigos! Olha só, a vodka está bem gelada, você vai adorar, nazdoroviya! Deixe-me colocar uns picles e um presunto defumado na mesa.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Uau... Então, me d-diz, Fadey, c-como é que isso f-funciona? Hic! A gente já bebeu... d-duas g-garrafas de v-vodca... aliás! - você tá p-parecendo sóbrio como uma pedra e eu... bêbado feito um gambá. Como é que pode, hein?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, meu amigo, relaxa. O que um gambá tem a ver com isso tudo? Acabamos de tomar uma vodka excelente. Vai dormir um pouco e você vai acordar renovado, com energia. Até sua cabeça vai clarear, sem ressaca nenhuma. Você vai ver.";
			link.l1 = "S-sim, vodka... é... é absolutamente magnífica, essa vodka. Nunca bebi nada parecido.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha! Isso mesmo! Esse tipo de vodca era feito segundo receitas secretas e trazido da minha terra natal, a Rússia, e mesmo lá nem todo mundo sabe preparar direito. Eu só compro o melhor! Como essa aqui, que nós dois tivemos a sorte de provar.";
			link.l1 = "M-mas me conta, Fadey: c-como é que você consegue beber t-tanto e não ficar bêbado? C-como faz isso, hein? D-divide esse segredo comigo. T-talvez me ajude mais tarde... Hic!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Ora, você não pode se comparar a mim, jovem Charles! Olhe pra você, magro feito um graveto. Além disso, nem está acostumado a beber de verdade, né! Mas como somos bons amigos, vou te contar uns segredos de como beber e não acabar se mijando todo.";
			link.l1 = "P-por favor, f-faça... hic!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Well, if you want to drink and not get instantly blasted, you must follow a few key rules. Most importantly, never drink on an empty stomach. Eat something hearty before the drinking session starts\nSecond, don't forget to eat something after every glass. Meat or fish is best, something nice and salty. Third, don't rinse your mouth with the vodka, swallow it at once\nAlso, having a small - no more than half a pint - shot before the main course will prepare your body for receiving serious doses of alcohol. Don't overdo this appetizer, otherwise the effect will be quite the opposite and you'll wreck yourself before setting sail\nFinally, disciplined training is key; drinking moderate amounts of rum or other types of alcohol on a regular basis will make you more resistant to them.";
			link.l1 = "Hm-mm... E-então é assim que se faz! Eu v-vou com certeza... hic!.. lembrar de todas as suas in-struções, Fadey. O-obrigado. E a-agora acho que seria uma b-boa ideia eu t-tentar dormir um pouco, porque não estou me sentindo muito bem agora.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Descanse um pouco, Charles. Tivemos uma noite agradável, você e eu! Boa sorte na caçada!";
			link.l1 = "D-d-do svidaniya, Fadey! Eu vou para - hic! - o Realizador de Desejos!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "O quê, ele realmente disse que eu iria te ajudar?";
			link.l1 = "É, mais ou menos isso. Vai ajudar o irmão do seu velho amigo? Não estou pedindo esmola como um mendigo. Só quero uma chance de ganhar algum dinheiro.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Oh Charles! Você chegou tarde. Se tivesse vindo antes, eu teria encontrado algo perfeito para você, mas agora – me perdoe. Não se preocupe, ande pelas cidades, converse com as pessoas. Há muito trabalho a ser feito no Caribe";
			link.l1 = "Entendo, que pena. Adeus!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hm. Não, claro que não vou recusar você. Se quiser alimentar um homem, não dê um peixe, mas sim uma vara de pescar. Não é assim, Monsieur de Maure? Então você precisa de trabalho... Isso é fácil. Vou conversar com um conhecido e vou recomendar você a ele. O resto vai depender de como você se sai no serviço.";
			link.l1 = "Maravilha. Com quem eu preciso falar?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Passe na loja amanhã. Um homem chamado Gerard LeCroix vai estar te esperando lá. Ele vai te passar um serviço. Ele só vai ficar nesta colônia até amanhã à noite. Procure-o logo e faça o trabalho direito. Não me coloque numa situação difícil.";
			link.l1 = "Fechado. Obrigado, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ah, como posso ajudar você, meu amigo?";
			link.l1 = "Fadey, escuta, eu realmente preciso comprar cinquenta escravos dos contrabandistas. O problema é que eles não me conhecem e preciso que você me apresente. Sem você, eles nem vão me dar ouvidos, e isso é uma questão de vida ou morte para uma pessoa muito importante.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho! Expandindo seus negócios, hein! Que lucrativo! Eu vou te ajudar, meu caro amigo. Mas como você sabe, não trabalho de graça. Vai custar 150 dobrões de ouro para convencer o vendedor das suas boas intenções ao comprar os negros e, claro, um extra pelo meu esforço dedicado...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Eu não esperava menos, Monsieur Fadey! Aqui está o seu ouro.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Vou ao agiota agora mesmo! Espere aí, Monsieur Fadey, já volto!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, parece que tive uma ideia e não preciso mais dos negros. Me desculpe. Até logo!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Excelente, amigo. Mas se estiver tentando me enganar sobre a sua necessidade dessa compra e suas intenções forem inúteis, vai me deixar muito irritado. Você não vai querer isso. Amanhã, às dez horas, ao pôr do sol, na Praia Capster, vou marcar um encontro para você. Não me decepcione.";
			link.l1 = "Não se preocupe, eu volto para pegar a mercadoria.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Olá, olá! Diga-me, meu caro, o que traz você à minha modesta casa?";
			link.l1 = "Eu preciso de armas. Os comerciantes locais não conseguem encontrar a quantidade que eu preciso, mas acho que você pode me ajudar.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Antes de tudo, me diga exatamente do que você precisa, meu caro amigo. Depois eu te digo se posso te ajudar.";
			link.l1 = "Preciso de 30 pistolas de soldado, dois mosquetes de mecha, 70 cartuchos para eles e 90 poções de cura.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", você está me assustando. Primeiro cinquenta negros, depois armas. Está tentando começar uma revolta de escravos, meu amigo?";
					link.l1 = "Muito perspicaz, Fadey. Como eu disse antes, tudo isso é necessário para salvar uma pessoa importante. Não se preocupe, ela será tirada das garras dos espanhóis, então sua reputação aqui não será afetada.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "Que bom saber disso. Posso ajudar.";
			link.l1 = "Fico feliz em saber disso. Quanto?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Fico feliz que você tenha se explicado. E se isso realmente tiver algo a ver com os espanhóis, então vou te ajudar. Mas se descobrir que você me enganou, vou ficar muito bravo.";
			link.l1 = "Confie em mim, Fadey. Quanto?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Certo, então ... pistolas e alguns mosquetes, com pólvora e chumbo para cada um... Sendo assim ... não posso prometer que vou conseguir absolutamente tudo o que você pediu, mas farei o possível. Enquanto isso, preciso de um adiantamento de 40.000 pesos, ou 75 dobrões, se preferir.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Fique com os dobrões, Fadey. Por acaso estou com alguns aqui agora.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Todas as minhas dobrões se foram, aceita pesos, Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Preciso falar com meu banqueiro. Já volto!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Desculpe, Fadey, mas não posso pagar por isso. Vou tentar me virar sozinho. Até mais!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Volte amanhã, "+pchar.name+", e eu vou providenciar os materiais que você precisa.";
			link.l1 = "Então não vou atrapalhar. Até amanhã!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Volte amanhã, "+pchar.name+", e eu vou providenciar os materiais que você precisa.";
			link.l1 = "Então não vou atrapalhar. Até amanhã!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Olha, meu rapaz, tive sorte de conseguir tudo o que você pediu com tão pouco tempo. Devia me agradecer! Agora, o pagamento final. Me dê exatamente o mesmo valor que deixou de adiantamento, e pode pegar suas armas.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Pegue 75 doblões. Vou mandar meus homens levarem as armas para o meu navio. O que eu faria sem você, Fadey? Você não faz ideia do quanto me ajudou!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Leve 40.000 pesos. Vou mandar meus homens levarem as armas para o meu navio. O que eu faria sem você, Fadey? Você não faz ideia do quanto me ajudou!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Caramba, como é que eu pude esquecer o dinheiro? Já volto.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Excuse me, Fadey, I'm broke. Keep the deposit; I hope it will be enough to cover your expenses for this deal, and I'll try to manage on my own. See you!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Ajudar quem precisa é uma honra. Ajudar quem paga é um prazer. Da próxima vez que estiver em Basse-Terre, não deixe de me visitar para dar um alô.";
			link.l1 = "Isso é um absurdo – estar em Basse-Terre e não ver meu amigo Fadey! Até a próxima!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Ajudar quem precisa é uma honra. Ajudar quem paga é um prazer. Da próxima vez que estiver em Basse-Terre, não deixe de me visitar para dizer oi.";
			link.l1 = "Isso é um absurdo – estar em Basse-Terre e não ver meu amigo Fadey! Até a próxima!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition
		
		//--> Дикая Роза
		case "WildRose_Fadey_4":
			dialog.text = "Que plano você colocou em ação, "+pchar.name+"! A intenção, sem dúvida, é nobre, mas será possível? Vinte anos podem mudar qualquer homem...";
			link.l1 = "Você tem razão, Fadey. Mas já investimos muito tempo e esforço, viemos de longe — e estamos quase lá. Descobrimos quase tudo sobre ele: o nome, o tempo de serviço na Marinha Real de Sua Majestade, o nome do navio em que serviu... e outros detalhes da sua história. O rastro termina no naufrágio que aconteceu perto do Cabo Catoche em junho de 1638.";
			link.l1.go = "WildRose_Fadey_5";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey");
		break;

		case "WildRose_Fadey_5":
			dialog.text = "Catoche? Oh-ho, meu amigo, eu não iria praqueles lados nem amarrado — por lá andam bandos de selvagens malditos. Se ele foi parar lá e não morreu no mar, então, tão certo quanto o dia, os desgraçados dos nativos fizeram dele jantar...";
			link.l1 = "Temos provas de que esse homem sobreviveu ao naufrágio e depois conseguiu chegar a Cuba. Talvez tenha encontrado seu fim por lá, mas pelo que ouvimos — era esperto o bastante para escapar das garras dos inquisidores. Pouco provável que tenha ficado em Cuba — é mais provável que tenha se estabelecido em algum dos povoados do Arquipélago...";
			link.l1.go = "WildRose_Fadey_6";
		break;

		case "WildRose_Fadey_6":
			dialog.text = "Muitas maravilhas acontecem neste mundo, meu amigo, e tudo é possível. Mas ainda não entendo por que você me contou tudo isso.";
			link.l1 = ""+npchar.name+", você tem mais contatos do que alguns governadores. Tenho certeza de que tem homens capazes por perto que podem cuidar de tarefas simples...";
			link.l1.go = "WildRose_Fadey_7_1";
			link.l2 = ""+npchar.name+", você é um homem respeitado e influente. Anda entre pessoas importantes e tem ótimas conexões. Tenho certeza de que seus interesses comerciais vão muito além da Guadalupe. Já que não pode cuidar de tudo sozinho, certamente conta com agentes de confiança e homens inteligentes, capazes de cumprir tarefas que não sejam muito complicadas...";
			link.l2.go = "WildRose_Fadey_7_2";
		break;

		case "WildRose_Fadey_7_1":
			dialog.text = "Você é um homem inteligente e perspicaz, "+pchar.name+". De fato, já lhe disseram isso antes. Tenho homens capazes e experientes, você fala a verdade. Mas me diga claramente — o que você quer que eles façam.";
			link.l1 = "Eu pediria que você os enviasse para várias colônias do Arquipélago para tentar descobrir algo sobre o homem que procuramos. Talvez alguém tenha ouvido falar dele, ou até o conhecesse pessoalmente. Naturalmente, eu arcaria com todas as despesas. "+npchar.name+", isso é muito importante para a Mary, e não temos mais a quem recorrer.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Fadey_7_2":
			dialog.text = "Você é um homem inteligente e perspicaz, "+pchar.name+". De fato, já lhe disseram isso antes. Tenho homens capazes e experientes, você fala a verdade. Mas me diga claramente — o que você quer que eles façam.";
			link.l1 = "Eu pediria que você os enviasse para várias colônias do Arquipélago para tentar descobrir algo sobre o homem que procuramos. Talvez alguém tenha ouvido falar dele, ou até mesmo o conhecesse pessoalmente. Naturalmente, eu cubro todas as despesas. "+npchar.name+", isso é muito importante para a Mary, e não temos mais a quem recorrer.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Fadey_8":
			dialog.text = "Posso recusar um amigo tão bom quanto você, "+pchar.name+"? Principalmente porque você está disposto a gastar com esse assunto divino. Então me diga o nome do homem que você deseja encontrar.";
			link.l1 = "Quanto ao nome, não tenho certeza, mas acho que ele podia se chamar Rupert Casper ou Joshua Northwood.";
			link.l1.go = "WildRose_Fadey_9";
		break;

		case "WildRose_Fadey_9":
			dialog.text = "Muito bem, vamos encontrar o sujeito se ele usou os nomes que você disse...";
			link.l1 = "Excelente, "+npchar.name+". Podemos discutir o pagamento pelos seus serviços?";
			link.l1.go = "WildRose_Fadey_10";
		break;

		case "WildRose_Fadey_10":
			dialog.text = "Um assunto desagradável, mas, infelizmente, necessário.";
			link.l1 = "Então vamos começar. Ele dificilmente se arriscaria entre os espanhóis ou holandeses. O homem deixou problemas em Antígua, então não faz sentido procurar lá, nem provavelmente em Barbados. Talvez ele tenha se estabelecido no Continente Ocidental, na Jamaica depois que os espanhóis foram expulsos, nas colônias francesas, ou até mesmo em assentamentos piratas.";
			link.l1.go = "WildRose_Fadey_11";
		break;
		
				case "WildRose_Fadey_11":
			dialog.text = "Vou ser direto, meu caro: em todo o tempo que vivi em Basse-Terre, nunca ouvi falar de um cavalheiro com nenhum desses nomes. Então não precisa procurar aqui. Em Martinica e São Cristóvão conheço alguns ingleses, mas ele também não está entre eles.";
			link.l1 = "Então a área de busca fica consideravelmente reduzida.";
			link.l1.go = "WildRose_Fadey_12";
		break;

		case "WildRose_Fadey_12":
			dialog.text = "Precisamos verificar Tortuga, com certeza — e vou mandar o mesmo sujeito a La Vega, Puerto Principe e Port-au-Prince. Vou despachar meus homens de confiança para Belize e Blueveld, e também para a Jamaica e Isla Tesoro.";
			link.l1 = "E quanto tudo isso vai me custar?";
			link.l1.go = "WildRose_Fadey_13";
		break;

		case "WildRose_Fadey_13":
			dialog.text = "São homens experientes e trabalhadores, por isso, para cada um deles, você pagará cento e cinquenta doblões. O emissário que envio para Tortuga e Hispaniola junto com Cuba deve receber uma recompensa extra — cinquenta moedas de ouro a mais. Afinal, quatro assentamentos não são um só.";
			link.l1 = "Então isso dá 800 doblões... Podemos prosseguir com o acerto de contas?";
			link.l1.go = "WildRose_Fadey_14";
		break;

		case "WildRose_Fadey_14":
			dialog.text = "Certo, por que perder tempo? Você tem o valor exigido com você, meu bom homem?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Claro. Aqui, pegue.";
				link.l1.go = "WildRose_Fadey_14_pay";
			}
			else
			{
				link.l1 = "Hmm... Eu não tenho o valor total comigo.";
				link.l1.go = "WildRose_Fadey_14_nopay";
			}
		break;

		case "WildRose_Fadey_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Excelente, meu caro amigo! Vou enviar ordens escritas aos meus agentes imediatamente, e eles começarão a trabalhar. Eles precisarão encontrar navios que sigam para lá, o que pode levar algum tempo. A viagem em si depende da força do vento, e isso está nas mãos de Nosso Senhor. Mas acredito que meus homens devem voltar dentro de um mês.";
			link.l1 = "Então nos encontraremos em um mês, "+npchar.name+". Muito obrigado mais uma vez. Você foi de grande ajuda. Até lá!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2");
		break;

		case "WildRose_Fadey_14_nopay":
			dialog.text = "Eu entendo, "+pchar.name+", a quantia é considerável. Vou te esperar na minha casa assim que você conseguir o dinheiro.";
			link.l1 = "Volto logo.";
			link.l1.go = "exit";
			pchar.questTemp.WildRose_Etap5_Fadey_2 = true;
		break;

		case "WildRose_Fadey_return":
			dialog.text = "Eu me lembro do seu assunto, meu caro amigo. Suponho que você já conseguiu as oitocentas dobras de ouro?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l21 = "Aqui está, Monsieur Fadey! Aqui está o seu ouro. Tudo conforme combinado.";
				link.l21.go = "WildRose_Fadey_14_pay";
			}
			link.l31 = "Ainda estou juntando a quantia necessária, mas não se preocupe — não vou demorar muito.";
			link.l31.go = "exit";
		break;

		case "WildRose_Fadey_16":
			dialog.text = "Deu certo, meu amigo — ah, como deu certo! Todos os meus homens voltaram de mãos vazias, exceto por uma coisa. Jerome Sauvernier, que enviei para Belize, não voltou — mas mandou notícias. Boas notícias para você.";
			link.l1 = "Ele te enviou uma carta? Podemos lê-la?";
			link.l1.go = "WildRose_Fadey_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Fadey_17":
			dialog.text = "Claro, "+pchar.name+". Guardei especialmente para você, sabendo que iria querer ler. Por favor, meu amigo.";
			link.l1 = "Obrigado, vamos ler agora.";
			link.l1.go = "WildRose_Fadey_18";
			AddQuestRecordInfo("WildRose_Records_6", "1");
		break;

		case "WildRose_Fadey_18":
			dialog.text = "Faz tempo que não vejo um sorriso assim no seu rosto, meu bom homem!";
			link.l1 = "Não é de se admirar, "+npchar.name+"! Esperamos tanto tempo! Mas sabe, sempre acreditamos que ia dar certo! Não sei nem como te agradecer por ter sido tão importante nisso.";
			link.l1.go = "WildRose_Fadey_19";
		break;

		case "WildRose_Fadey_19":
			dialog.text = "Ah, pare com isso, meu caro! Você é meu amigo, e amigos devem se ajudar. Volte logo para mim — tenho certeza de que Monsieur Jerome vai se recuperar rápido e embarcar no primeiro navio...";
			link.l1 = "Acho que vamos acelerar as coisas. Vamos até Belize nós mesmos e conversar com o seu agente. Mais uma vez, obrigado, "+npchar.name+". Você não faz ideia do que fez por nós! Até a próxima!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_5");
		break;
		//<-- Дикая Роза
		
		//--> LoyaltyPack
		case "LoyaltyPack_Fadey_1":
			dialog.text = "Meu caro amigo Alonso Pimentel, que serve em seu navio? Ha! Mas é claro. Toda vez que seu navio atraca, esse bom sujeito sempre passa aqui para um drinque. Poucos amigos me restam, "+pchar.name+". Eu guardo cada uma delas como um tesouro.";
			link.l1 = "O Alonso me contou histórias incríveis sobre suas aventuras na guerra. Ele até me deu seu bandoleiro.";
			link.l1.go = "LoyaltyPack_Fadey_2";
			DelLandQuestMark(npchar);
		break;

		case "LoyaltyPack_Fadey_2":
			dialog.text = "Espero e confio que ele tenha guardado as mais notáveis para si. Mas já que Alonso compartilhou nossa amizade com você, também tenho uma curiosidade para lhe mostrar. Veja!";
			link.l1 = "Isso é... uma armadura?";
			link.l1.go = "LoyaltyPack_Fadey_3";
		break;

		case "LoyaltyPack_Fadey_3":
			dialog.text = "Ah, meu amigo. Isso é tudo o que restou da minha armadura de espelhos que usei durante aquela guerra maldita. E depois, perto de Smolensk, tive a ocasião de\n"+" Seja como for, mesmo assim ela continua magnífica e protege ainda melhor. E agora não me serve mais de jeito nenhum!";
			link.l1 = "Parece exótico... até mesmo para estes lados. Um presente magnífico, Fadey. Obrigado.";
			link.l1.go = "LoyaltyPack_Fadey_4";
		break;
		
		case "LoyaltyPack_Fadey_4":
			dialog.text = "Para você, meu amigo, apenas mil dobrões.";
			if (PCharDublonsTotal() >= 600)
			{
				if (GetSummonSkillFromName(pchar, SKILL_Commerce) >= 60)
				{
					link.l1 = "Permita-me corrigir você, caro Fadey. Mil doblões seria pelo conjunto completo de armadura. Mas só pelo peitoral?";
					link.l1.go = "LoyaltyPack_Fadey_5";
					Notification_Skill(true, 60, SKILL_COMMERCE);
				}
				else if (PCharDublonsTotal() >= 1000)
				{
					link.l1 = "Não me surpreende que você e Alonso se deem tão bem. Aqui está o seu ouro.";
					link.l1.go = "LoyaltyPack_Fadey_1000";
					Notification_Skill(false, 60, SKILL_COMMERCE);
				}
			}
			link.l2 = "Ha! Você quase me pegou dessa vez, Fadey! Quem sabe numa próxima.";
			link.l2.go = "LoyaltyPack_Fadey_MoneyLater";
		break;
		
		case "LoyaltyPack_Fadey_MoneyLater":
			dialog.text = "Claro, sem pressa. Minha armadura de espelho vai estar sempre te esperando.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LoyaltyPack.Fadey = "money";
		break;
		
		case "LoyaltyPack_Fadey_5":
			dialog.text = "Oh, você é esperto mesmo! Muito bem, eu deixo por seiscentas moedas de ouro.";
			link.l1 = "Não é à toa que você e Alonso se dão tão bem. Aqui está o seu ouro.";
			link.l1.go = "LoyaltyPack_Fadey_600";
		break;
		
		case "LoyaltyPack_Fadey_1000":
			dialog.text = "Um bom negócio. Agradeço e confio minha armadura espelhada a mãos dignas. E cuide do Alonso, capitão.";
			link.l1 = "Quem está cuidando de quem aqui...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(1000);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_600":
			dialog.text = "Um bom negócio. Agradeço e confio minha armadura espelhada a mãos dignas. E cuide do Alonso, capitão.";
			link.l1 = "Quem está cuidando de quem aqui...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(600);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_end":
			DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_Fadey_DlgExit");
		break;
		//<-- LoyaltyPack

		case "guardoftruth":
			dialog.text = "Bem, quem diria que você viria a negócios, meu amigo! Infelizmente, não tenho vodka para te oferecer agora, bebi tudo. Me conte, em que encrenca você se meteu desta vez.";
			link.l1 = "Uma paróquia local recebeu de um certo corsário uma cruz peitoral de ouro com lazurita, em troca do perdão de seus pecados. É uma peça única e muito valiosa. O problema é que essa cruz foi roubada de outra paróquia. E, além disso, um padre foi assassinado durante o roubo.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ó imaculada Theotokos! Não diga!";
			link.l1 = "Sim. Estou representando os paroquianos roubados e tentando devolver a cruz aos seus verdadeiros donos.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Um ato nobre, e bem piedoso. Tentando ganhar pontos com o Todo-Poderoso?";
			link.l1 = "Mas o padre local se recusa a me devolver, apesar de tudo que contei a ele. Não entendo. Como alguém pode colocar tranquilamente uma cruz roubada, manchada com o sangue de um homem inocente, na Casa de Deus? Isso é blasfêmia!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Bem, tecnicamente todo cálice consagrado carrega o sangue do Cristo Inocente... mas estou me desviando. Imagino que você queira minha ajuda?";
			link.l1 = "Eu sei! Você tem muita influência em Basse-Terre. É bem respeitado, então talvez o padre escute seus conselhos.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", você contou ao nosso padre a história exata dessa cruz roubada?";
			link.l1 = "Claro! Apelei para os sentimentos religiosos dele, para a solidariedade cristã, para a maldita consciência dele, pelo amor de Deus, mas ele fechou os ouvidos.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Você já tentou outros métodos para convencê-lo?";
			link.l1 = "Você quer dizer suborná-lo? Eu não vou subornar um padre. Se ele fosse um banqueiro, um comerciante, ou até mesmo um governador, eu até tentaria resolver assim, mas um padre, não!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "My dear naive friend, if the priest's ears truly are closed to proclamations of conscience, then surely his hands will be open to gold... Or perhaps the other way around. I'll help you; I think that keeping such a tainted treasure here is bound to cause greater trouble down the road. However, it will require certain expenses."link.l1 = "Por que eu não estou surpreso? Quanto é desta vez?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Passe aqui amanhã, "+pchar.name+", ainda não posso dizer o preço. Mas você terá aquela cruz roubada, pode ter certeza.";
			link.l1 = "Muito bem, Fadey, não vou mais te incomodar então. Até amanhã!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Como prometido, consegui a cruz. Quanto aos detalhes... ah, esqueça isso... todas as bobagens perdoadas pelo sangue derramado do nosso Precioso Salvador";
			link.l1 = "Quanto eu te devo?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Duzentos e cinquenta doblões. Para cobrir minhas despesas e, claro, eu agradeceria um extra pela minha ajuda justa...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Aqui está o seu ouro, Monsieur Fadey.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "Preciso pegar o ouro na minha cabine. Já volto.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Certo. Aqui está a cruz roubada.";
			link.l1 = "Obrigado, Fadey. Você nem imagina o quanto fez por mim!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sempre fico feliz em ajudar um amigo gentil – e, mais importante ainda – generoso. Passe por aqui mais vezes. Quem sabe, quando chegar da terra natal, a gente toma uma vodca.";
			link.l1 = "Com prazer!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Ora, ora, o mar ainda não te levou! Conte-me tudo. Que desventuras te trouxeram à minha porta desta vez?";
			link.l1 = "Não sei se devo chamar isso de infortúnios ou não, mas, de todo modo, estou aqui. Fadey, no primeiro dia em que nos conhecemos, você me deu uma adaga rara, a Garra do Chefe. Agora descobri que ela pertencia antes a um homem chamado Archibald Calhoun. Por favor, me conte o que você sabe sobre esse homem.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Nada escapa de você, "+pchar.name+". Você enxerga tudo, igualzinho ao seu irmão. Sim, ganhei esta adaga num jogo de dados do Calhoun. Quem é ele? Eu mesmo não faço ideia. Nos conhecemos por acaso na taverna, começamos a conversar, tomamos uns drinks, e ele começou a me contar sobre alguns pecados do passado que ainda o atormentavam...";
			link.l1 = "O que você é, o confessor dele? Que pecados?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald era assombrado pela lembrança de um homem que foi torturado até a morte pela Inquisição por causa dele, junto com outras almas inocentes que ele matou. Ele vivia se chamando de Judas, dizendo que Deus o estava castigando por seus pecados e que a Inquisição estava em seu encalço. Comentou que o inquisidor espanhol Vincento queria vê-lo morto e tinha mandado mercenários atrás dele por todo o Caribe. Depois, o álcool falou mais alto e apostamos essa adaga velha.";
			link.l1 = "É só isso? Nunca mais viu ele?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Claro que não, ele está morto agora. Um bando de piratas miseráveis mandou o fluyt dele para o fundo do mar e toda a tripulação para Mictlantecuhtli. Pra falar a verdade, diziam que foram atacados por profissionais disfarçados de piratas... agentes da Inquisição. Dizem que o padre Vincento sempre pega o homem que procura.";
			link.l1 = "Archibald Calhoun está vivo. Eu o vi não faz muito tempo, junto com um tal de William Paterson. Ele serve como imediato dele.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Oh ho, que surpresa! Pelo menos o Archibald pode respirar aliviado sob a asa do Capitão Paterson. Está em boa companhia. Os espanhóis temem o Paterson como à peste. Não vão ousar tramar nada contra o Archibald enquanto ele estiver sob a proteção do Paterson.";
			link.l1 = "Você conhece o Paterson?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Quem não conhece William Paterson!? Ele também é recém-chegado ao Caribe, assim como você. E, assim como você, já construiu uma reputação impressionante. O Sr. Paterson é o amigo mais próximo do Coronel Fox e tem grande influência até com Lord Windsor, o Governador-Geral de todas as colônias inglesas no Caribe. Ele costuma visitar o palácio do governador em Port Royal, na Jamaica.";
			link.l1 = "Entendi. Obrigado pela informação, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Ah, não foi nada, amigo. Venha me visitar qualquer dia! Boa caçada!";
			link.l1 = "Com certeza!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Vamos dar uma olhada, "+pchar.name+"... Sim! É um deles! Esse é meu garoto, você salvou meu dia! Onde você achou isso?";
			link.l1 = "Não importa. O que realmente importa é que isso voltou para você.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "Vou pagar bem pela sua investigação detalhada. Trezentos dobrões de ouro devem ser uma recompensa suficiente pelo seu trabalho...";
			link.l1 = "Vai me pagar com alguns daqueles dobrões que arrancou de mim antes? Embora, é claro, não vou recusá-los. Aqui está seu shamshir.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Obrigado, meu amigo! Agradeço pela espada e pelas suas palavras sarcásticas. Você é mais sábio do que aparenta ser para sua idade, "+pchar.name+", mas os laços humanos da amizade valem mais do que ouro. Falando em ouro, - vou te pagar tudo. Aqui, pegue seus dobrões.";
			link.l1 = "Obrigado.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "E falando sobre os laços da amizade, especialmente os nossos, "+pchar.name+". Eu tenho algo que vai te interessar muito.";
			link.l1 = "Deixa eu adivinhar, mais vodka?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ha! Vodka é boa, mas não é a única coisa pela qual meu país é conhecido. Existe um material especial que só a Rússia produz. Eu mando trazer esse material pelos meus contatos de lá para negociar aqui. Todo capitão quer, porque melhora qualquer navio. Estou falando das cordas de cânhamo\nCordas imunes à umidade e ao sal do mar. Dizem que é o melhor material para o cordame\nTodo mês, recebo uma certa quantidade vinda de Reval. Normalmente, meu armazém tem algumas centenas de rolos por volta do meio de cada mês. Então, "+pchar.name+", I am offering to sell you a batch of fifty coils. Ten doubloons a coil\nI have only two terms: first, I will keep your ropes until the 20th of every month; second, you can buy only the whole batch. Fifty coils for five hundred doubloons. Confidentially speaking, "+pchar.name+", they say that there are certain places where you can resell those ropes for a much greater price, but what do I know!\I am completely satisfied with the current state of my operation and don't need to find resellers myself. If you find a good merchant, you can turn a fine profit.";
			link.l1 = "Entendi. É uma ótima proposta, Fadey! Acho que vou aproveitar a oportunidade que você está me dando. Então, no vigésimo dia de cada mês, quinhentos dobrões por cinquenta peças?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Sim. Vá buscar sua compra. Mas espere, espere, meu caro! Além deste shamshir, que você me devolveu por pura bondade, havia outros dois. Por favor, eu lhe peço, se encontrá-los, traga-os de volta para mim e eu lhe pagarei mais do que um preço justo pela devolução.";
			link.l1 = "Com certeza, Fadey. Se eu encontrá-los, vou trazê-los de volta.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Boas notícias para você. Consegui outro shamshir persa.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Oh, meu bom amigo! Você acabou de enxugar minhas lágrimas! Deixe-me ver... Ah! É isso mesmo, minha preciosa shamshir! Aqui está, como prometido, trezentos dobrões como recompensa.";
			link.l1 = "Spasibo!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Por favor, aceite minha gratidão e um presente modesto, mas muito útil. Eu não preciso dele, mas você ou o carpinteiro do seu navio vão achar bastante valioso\nVeja só este anel elegante! Agora é seu. Mas não é um anel qualquer, é um anel encantado. Ele ajuda na carpintaria e nos reparos do navio. Muitos artesãos gostariam de tê-lo, mas eu o guardei para uma ocasião especial. Fique com ele, meu amigo, espero que alivie um pouco o seu fardo!";
			link.l1 = "Você certamente carrega muitos artefatos interessantes. Obrigado, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Só falta um shamshir da minha coleção perdida para ser encontrado. Estou contando com você, "+pchar.name+", e da sua sorte. Se encontrar, não hesite em voltar correndo para mim.";
			link.l1 = "Com certeza! Até logo...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Por que eu deveria me apressar? A espada está comigo.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Graças a Deus que pedi sua ajuda, "+pchar.name+". Você é um homem milagroso, meu amigo! Mostre pra mim... Ohooo! É, é ela. Minha querida! Krasavitsa! Muito obrigado, meu caro, faço uma reverência a você! Aqui, aqui está seu dinheiro. Quatrocentos doblões e nem uma moeda a menos! Não vou ser mesquinho.";
			link.l1 = "Obrigado, Fadey. É um prazer ajudar.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "Minha coleção de shamshirs está completa novamente! Ninguém vai ousar roubá-la de mim outra vez, disso eu mesmo vou cuidar! Tenho uma recompensa muito especial para você, meu amigo. Em duas semanas, um comerciante vai me trazer uma armadura de esgrima excelente, vinda da Europa. Encomendada por um nobre, é realmente uma peça única.  Então, se quiser, pode comprá-la por apenas setecentos dobrões de ouro. Direi ao nobre que ela se perdeu no transporte.";
			link.l1 = "O que há de tão especial nessa armadura?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "É muito confortável e resistente, mas ainda assim protege tão bem quanto uma couraça de ferro. E além disso, é linda! Volte daqui a algumas semanas para dar uma olhada. Mas não demore mais de um mês, senão vou vender para o cliente original.";
			link.l1 = "Combinado. Passo na sua casa daqui a duas semanas.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Sim, já foi entregue e está esperando por você. Trouxe o dinheiro?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Sim. Aqui estão setecentos doblões.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Droga. Esqueci o dinheiro no navio. Vou buscar e já volto!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Sim, meu bom homem! Aqui, pegue. Esta armadura de vime vai te servir muito bem, eu garanto. Não há nada igual, em todo o Caribe!";
			link.l1 = "Sim, eu percebo isso. Obrigado! Mal posso esperar para experimentar...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Por que você precisa esperar? Vai em frente. Vamos ver como fica.";
			link.l1 = "Pode deixar. Até mais, Monsieur Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Entre, meu caro amigo. A mercadoria está pronta para você comprar. 2.125 doblões por duzentas e cinquenta peças.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Está tudo conforme combinamos. Pegue o dinheiro.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Deixe-me só pegar as moedas na minha cabine.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Entre, meu caro amigo. A mercadoria está pronta para você comprar. Quinhentos doblões por cinquenta peças.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Está tudo como combinamos. Pegue o dinheiro.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Deixe-me só pegar as moedas na minha cabine.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadey, será que podemos aumentar o volume dos nossos negócios? Estou pronto para comprar cinco vezes mais mercadorias de você! Acho que isso seria bom para nós dois. O que me diz?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadey, eu trouxe o dinheiro! Três mil dobrões de ouro, como combinado.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Foi um prazer fazer negócios com você, "+pchar.name+". Vou mandar meus homens trazerem as cordas para o seu navio.";
			link.l1 = "Obrigado!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Se ainda precisar de mais cordas, volte daqui a um mês.";
			link.l1 = "Muito bem, Fadey. Até mais!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "O que posso fazer por você, meu caro amigo?";
				link.l1 = "Você é um homem influente, Fadey. Amigo do governador e, dizem os boatos, tem contatos na corte. Você conseguiria interceder junto às autoridades caso eu tenha problemas com a lei?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "Como posso ajudar você, meu amigo?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Estou com um problema com as autoridades inglesas.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Estou com problemas com as autoridades francesas.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Estou com um sério problema com os contrabandistas.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Desculpe, acho que posso me virar sozinho.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh ho ho, meu caro, quem foi que te disse isso? Todo mundo mente. Mas já que você é irmão do Michel e um bom amigo meu, posso tentar resolver as coisas pra você. Posso interceder apenas junto às autoridades inglesas e francesas, embora meus contatos tenham seus limites. Não faço negócios com espanhóis nem holandeses.\nTambém te aviso que minha influência só basta pra te livrar de encrencas pequenas. Posso convencê-los a reconsiderar sua postura se for uma falta leve ou amenizar alguma irritação passageira. Mas se você for arrumar uma guerra, não espere que eu vá salvar sua pele!\nAlém disso, só consigo acalmar uma nação por vez: França ou Inglaterra. Não posso me dividir pra fazer dois trabalhos ao mesmo tempo. E claro, vai ser preciso um pouco de dinheiro pra subornar as pessoas certas. Se achar meus termos aceitáveis, não hesite em me procurar.";
			link.l1 = "Obrigado, Fadey. Vou lembrar disso.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.FadeyNation));
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", false);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Of course. I have certainly heard of your adventures - or misadventures. I can take care of your little problem; nothing that the right amount of gold greasing the right palms can't fix. " + sTemp + " and I'll pull you out of the cookpot.";
				if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
				{
					link.l1 = "Ótimo! Aqui está o ouro.";
					link.l1.go = "agree";
				}
				link.l2 = "Então é a hora certa para eu ir buscar as moedas.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Of course. I have certainly heard of your adventures - or misadventures. I can take care of your little problem; there's nothing that the right amount of gold greasing the right palms can't fix. " + sTemp + " and I'll pull you out of the cookpot.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "Ótimo! Aqui está o ouro.";
						link.l1.go = "agree";
					}
					link.l2 = "Então é o momento perfeito para eu ir buscar as moedas.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Sim, você está mesmo numa enrascada! Não posso resolver totalmente essa situação. Posso, no entanto, amenizar o impacto do raio que está prestes a cair sobre sua cabeça pecadora. E depois, a qualquer momento, podemos tentar subornar de novo, se você tiver dinheiro e vontade. "+sTemp+" e eu posso começar a resolver seus problemas.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "Estou cansado desses caçadores de piratas me perseguindo. Aqui está o ouro.";
						link.l1.go = "agree";
					}
					link.l2 = "Então é a hora certa para eu ir buscar as moedas.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Certo, me dê uns dez a quinze dias. Enquanto isso, vou providenciar tudo e cuidar dos detalhes. Em cerca de duas semanas estará tudo pronto. ";
			link.l1 = "Obrigado, Fadey! Vou ficar esperando...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.FadeyNation));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", true);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			dialog.Text = "Por que você foi irritar esses caras, meu caro? Os contrabandistas nem são as piores pessoas por aqui, e ainda podem te render um bom lucro. Tá bom, eu vou te ajudar, sei como agradar esse tipo de gente... Vai ser "+sTemp+", sem pechinchar.";
			if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
			{
				Link.l1 = "Muito bem, Fadey, eu concordo. Pegue seu ouro.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Eu não tenho tanto ouro comigo agora. Volto mais tarde!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Está bem, eu vou resolver essa briga, pode deixar. Eles vão voltar a fazer negócios com você, como nos velhos tempos.";
			Link.l1 = "Obrigado!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, vejo que seus negócios estão prosperando e o apetite só aumenta! Você tem razão, nossos produtos são de qualidade e os preços não são tão altos. Mas olha, é preciso investir! Um negócio desses exige seriedade pra que tudo saia perfeito.";
			link.l1 = "Você acha mesmo que eu viria até você com uma proposta dessas sem ter umas centenas de dobrões guardados?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "Eu sei que você tem moedas guardadas no baú, e não são só algumas, com certeza caberiam cinquenta! Mas o nosso negócio não é comum – não se trata só de transportar mercadorias, mas de encontrar um jeito... digamos, discreto. Para esse volume, você vai precisar investir pesado, não apenas pagar, para que seja realmente lucrativo! E para garantir que seu dinheiro não desapareça no ar. Se estiver disposto a se separar de três mil dobrões de ouro, pode confiar na minha palavra: tudo será feito do jeito certo pra você, como um bom amigo, e não vamos te passar a perna no preço.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Três mil doblões! Ora, devo admitir, uma oferta tão generosa raramente se ouve, nem mesmo entre os mercadores mais prósperos, nem nas histórias mais fantásticas! Poucos estão dispostos a investir tão generosamente numa empreitada dessas. Mas eu, felizmente, sou um deles. Aqui está o seu dinheiro, Monsieur Fadey.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Três mil dobrões de ouro! Não estou preparado para uma quantia dessas, Fadey. Infelizmente. Eu volto mais tarde.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Três mil, você disse? Bem... Para ser sincero, uma quantia dessas impõe respeito à sua ambição. Mas devo admitir - isso não é para mim.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Que reviravolta! Você chega com uma proposta e logo depois volta atrás! Admito, fiquei decepcionado, mas não vou deixar isso estragar nossa amizade. Vamos deixar tudo como estava: nosso acordo anterior continua - cinquenta rolos a dez dobrões cada, todo mês, no dia 20.";
			link.l1 = "Que bom que você me entende, Fadey. Eu até gostaria de mudar de ideia, mas esses gastos estão além do que posso pagar. Infelizmente, meus recursos são limitados nesse assunto.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Bem, se essa é a sua decisão, não há mais o que discutir. Isso não vai afetar nossa amizade. Venha me visitar, "+GetSexPhrase("meu bom senhor","bela dama")+".";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "Agora sim, isso é sensato! Você não perde tempo com conversa fiada, mas sabe agir. Pra gente de negócios como você, sempre tem um desconto especial! Quinze por cento de desconto em todos os próximos carregamentos! Nosso acordo é o seguinte: 250 rolos de corda de cânhamo que vou deixar prontos pra você todo mês. Você pode buscá-los, como antes, no dia 20, pagando 2125 doblões por tudo, sem resto.";
			link.l1 = "Perfeito, Fadey! Fazer negócios com você é surpreendentemente fácil. Tenho certeza de que o sucesso nos espera. Até a próxima!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}