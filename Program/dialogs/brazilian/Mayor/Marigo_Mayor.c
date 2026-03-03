// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pode perguntar.","Estou ouvindo, qual é a sua pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados."),"É verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Sinto muito, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Sua Graça, trago notícias absolutamente excelentes e urgentes! Capturei Bartolomeu, o Português, o desgraçado está sob custódia e aguardando um julgamento justo! E espero receber algum reconhecimento modesto da Companhia...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "Foi o senhor quem fez questão de me receber, Senhor Governador...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "Estou aqui para tratar do assunto dos espiões ingleses, senhor governador...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Você já levou tudo. O que mais você quer?","Ficou alguma coisa que você ainda não pegou?");
            link.l1 = RandPhraseSimple("Só estou dando uma olhada...","Só estou conferindo, posso acabar esquecendo de pegar alguma coisa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeu... Bart, o Português, está na minha cidade?! Vivo?!!";
			link.l1 = "Ele está, Vossa Graça, e sob guarda confiável. Eu o entregarei a você assim que receber a recompensa pela cabeça do Bart, como prometido pela Companhia. Dublões de ouro também servem...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Bill, dobrões? Você ficou louco?! O que você tinha na cabeça ao trazer esse monstro para a minha cidade?! Se ele está aqui, então a fragata dele não deve estar longe da ilha, e a tripulação pode estar na cidade neste exato momento!";
			link.l1 = "Eu matei aqueles que estavam com ele, não sei sobre os outros, mas acho que isso não importa muito porque Bartolomeo está...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Sim! Você realmente não entende o que fez?! O 'Albatross' está perto da ilha e você capturou o pirata cuja brutalidade assusta até sua própria tripulação sanguinária! Vá embora daqui! Saia da ilha! E leve esse monstro com você!";
			link.l1 = "Mas escute, e quanto à recompensa prometida e...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Eu não quero ver minha cidade em chamas por causa da sua ganância e da sede de vingança da Companhia! Só tenho recrutas inexperientes no meu forte, e metade deles vai fugir assim que souberem quem está atacando os nossos baluartes e por quê! E aí o massacre vai começar... Não vou arriscar, está me ouvindo?! Vá embora e entregue-o em Curaçao você mesmo, se a Companhia quer tanto a cabeça dele!  Faça isso imediatamente, antes que seja tarde demais! E pode fazer o que quiser com ele, até jogá-lo do convés do seu navio, só não faça isso na minha cidade!  Hans! Hans, onde você está, seu idiota preguiçoso! Traga uma poção de valeriana ou qualquer coisa, e alguém, pelo amor de Deus, tire esse aventureiro da minha residência!";
			link.l1 = "Mas Vossa Graça...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Muito bem! Diga-me, capitão, você encontrou algum navio militar ou mercante inglês ao se aproximar da nossa ilha?";
			link.l1 = "Não, senhor. Não vi nem embarcações militares nem mercantes sob a bandeira inglesa em suas águas.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Entendo. Quanto tempo espera ficar aqui?";
			link.l1 = "Uns três dias, mais ou menos...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "In that case, I have an offer for you. According to our intelligence, there is a risk of English spies here. I will give ten thousand pesos as a reward for any information regarding suspicious vessels or people on the island, in the town, its vicinity, on the shores, etc. The reward will be significantly increased if you assist the authorities in detaining or eliminating an enemy.\nEvery civilian captain is welcome to take part in the investigation and to patrol the local shores and jungle in search of spies.\nIt's possible that you'll encounter our military corvette, the Zeepard; don't be alarmed, it is on patrol. You are free to approach its captain if you find any Brits.";
			link.l1 = "Lamento, Vossa Excelência, mas estou aqui apenas com intenções pacíficas de comércio. Terei que deixar esta ilha assim que reabastecer e concluir meus negócios aqui.";
			link.l1.go = "FMQN_3";
			link.l2 = "Uma oferta tentadora! Acho que vou aceitar e atacar as águas e as costas da sua ilha. Talvez eu até fique por aqui por um tempo.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "É só uma informação, capitão. Sem pressão. Você sabe a quem procurar se notar algo suspeito.";
			link.l1 = "Muito bem, senhor, entendi. Adeus!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Excelente, capitão! Já que está levando isso tão a sério, não deixe de falar também com o nosso comandante. Ele é responsável por capturar espiões e pode lhe fornecer informações adicionais.";
			link.l1 = "Certo, senhor. Vou falar com ele.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "Estávamos esperando por você, Mynheer "+GetFullName(pchar)+". Allow me to express our gratitude for your actions in eliminating the dangerous English raiding party. Please accept these ten thousand pesos. In addition: 200 ship's silk will be loaded into your hold, and a very special reward — a three-year license from the Dutch West India Trading Company. This is an extremely valuable document; I trust you know that?";
			link.l1 = "Claro! Uma licença de três anos — isso é realmente algo grande.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Por favor, aceite sua recompensa. Além disso, pode contar com a gratidão de todos os cidadãos e autoridades holandesas. Você é uma sensação em Philipsburg, e ficaríamos felizes em vê-lo novamente.";
			link.l1 = "Ouvir palavras tão calorosas vale mais do que a licença. Obrigado, foi um prazer. Agora, devo seguir meu caminho. Adeus!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "Rendemo-nos! Em nome de tudo o que é sagrado, eu lhe suplico, não saqueie nem pilhe Philipsburg e seus cidadãos! Estou pronto para ouvir suas exigências!";
			link.l1 = "Não se preocupe com os cidadãos, Mynheer. Os súditos da Coroa Francesa não devem temer os soldados franceses.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "A Coroa Francesa?";
			link.l1 = "Exatamente. Esta ilha pertence à França, e vocês são apenas inquilinos aqui. Inquilinos insolentes, que acreditaram que esta ilha poderia ser sua propriedade. A partir de hoje, a autoridade holandesa em Saint Maarten chegou ao fim. Está claro?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "Mas... Mas o que vai acontecer conosco, com os soldados holandeses que se renderam a você, e com os feridos? E o que...";
			link.l1 = "Isso vai depender apenas de você, Mynheer Thomas. Se me fizer um favor, permitirei que todos os que se renderam levem seus feridos e partam daqui em um navio, ou navios, que encontraremos no porto, para Curaçao, para Mynheer Stuyvesant.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "Caso contrário, você será mantido nos porões dos meus navios e nas casamatas de Saint Kitts. Além disso, alguns importantes oficiais holandeses terão que ser enforcados, só para garantir que Stuyvesant perca o interesse em conquistar nossas colônias...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(gaguejando) O q-qu... que... sobre q-que t-tipo de  f-fav... or?";
			link.l1 = "Nas profundezas da ilha há um verdadeiro pomo da discórdia – uma mina de sal. Sei que lá não estão apenas mineiros e escravizados, mas também soldados holandeses, armados até os dentes. Devem ser da Guarda da Companhia, não é mesmo, Mynheer? Vou lhes dar a chance de se renderem, ou usarei a força se recusarem. Preciso de um guia que possa me mostrar o caminho até a mina. Encontre alguém assim para mim.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "S-Sal... m-mina?";
			link.l1 = "Exactly. Don't be afraid, Mynheer Thomas, if the guards of the mine are wise enough to give up their arms, I will give them an opportunity to leave the island. I don't need unnecessary bloodshed. Don't worry, your conscience will be clear: even if you don't tell me where the mine is, the island of Saint Maarten is small enough that I can find the mine without your help; I just don't want to waste my time rambling through thickets and marshes. So this deal is more profitable to you than it is to me.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "T-tá... bom, eu vou te contar como chegar à mina, m-mas você precisa me d-dar sua palavra que t-todos... todos nós vamos sair desta ilha!";
			link.l1 = "Dou-lhe minha palavra como oficial e nobre.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "Na baía de Grand Case... bem na ponta, perto da água, há... há pedras. Ali... ali, atrás delas, seguindo pela margem, existe uma passagem junto à água, lá... é raso ali, dá água na cintura ou menos. Você precisa contornar a pedra e vai chegar a uma praia grande, onde... onde não dá pra atracar o navio por causa dos recifes ao redor. Dessa praia sai um caminho que leva direto... para... para a mina.";
			link.l1 = "Excelente. Estou partindo. E você, senhor, ficará aqui sob a atenta vigilância dos meus soldados até que eu volte.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
