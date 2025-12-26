// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pode perguntar.","Estou ouvindo você, qual é a pergunta?"),"É a segunda vez que você tenta perguntar...","Já é a terceira vez que você tenta perguntar de novo...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda insiste em me perguntar algo!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados."),"É verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Sinto muito, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Tenho um assunto delicado para você. Não faz muito tempo, um corsário doou uma cruz de ouro com uma pedra de lazurita para a paróquia de Basse-Terre. O problema é que essa cruz foi roubada da paróquia de Santiago, e um clérigo foi assassinado durante o roubo...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Cheguei por ordem do Governador-Geral Philippe de Poincy para assumir o comando da sua fragata armada.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "Estou pronto para incorporar a fragata ao esquadrão.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "Tenho um encontro aqui com alguém...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Monsieur, pretendo iniciar atividades comerciais nesta cidade. Especificamente, tenho interesse no comércio constante e em grande escala de bebidas alcoólicas.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Você já pegou tudo. O que mais você quer?","Faltou pegar mais alguma coisa?");
            link.l1 = RandPhraseSimple("Só estou dando uma olhada...","Só estou conferindo, posso acabar esquecendo de pegar alguma coisa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. Isso é realmente interessante. Mas por que você acha que eu me importo com os problemas dos espanhóis?";
			link.l1 = "Não se trata dos espanhóis, Monsieur. A religião não divide as pessoas por nacionalidade. Há um objeto coberto com o sangue do servo sagrado em sua paróquia, e houve uma profanação cometida na paróquia de Santiago...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "Peço que seja justo e ordene ao padre que devolva a cruz aos seus verdadeiros donos.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "E desde quando você se tornou um crente tão verdadeiro e sincero, hein, "+pchar.name+"? Os espanhóis não são nossos amigos e não vejo motivo para pressionar o santo padre sobre esse assunto. A cruz foi um presente e está tudo bem. Nosso padre não tem ligação com aquele roubo e assassinato, então...";
			link.l1 = "E você não pode me ajudar, certo?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Para ser sincero, "+pchar.name+", não sinto que deva. Não tenho nenhum apreço por esses fanáticos papistas.";
			link.l1 = "Entendo. Desculpe incomodá-lo, Monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "O navio está pronto, mas você não tem uma vaga livre para ele no seu esquadrão. Capitão, reduza seu esquadrão e volte, então eu lhe entregarei a fragata imediatamente.";
				link.l1 = "Certo.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Sim, claro, o navio está pronto para zarpar. O capitão está ciente e seguirá todas as suas ordens.";
				link.l1 = "Então estamos partindo. Adeus, Vossa Graça.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excelente. Prepare-se para receber seu novo navio. O capitão já está ciente e seguirá todas as suas ordens.";
			link.l1 = "Então estamos partindo. Adeus, Vossa Graça.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ah, Monsieur Charles de Maure, que bom que chegou! Meu velho amigo está ansioso para conhecê-lo e pediu que eu o avisasse assim que chegasse. Por favor, venha até minha sala de estar, avisarei Angerran imediatamente. Aliás, como vocês dois se conheceram?";
			link.l1 = "Jogamos juntos. Ele perdeu, tivemos uma pequena briga. Suponho que o Monsieur de Chievous queira resolver as coisas entre nós.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "Sem dúvida! Espero que vocês dois consigam se entender. Angerran pode não ser a pessoa mais agradável de se lidar, mas é inteligente e honrado, assim como você. São qualidades raras.";
			link.l1 = "Vossa Excelência me lisonjeia. Esperarei por ele na sala de visitas, se não se importar.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "Mas é claro, fique à vontade, sinta-se em casa. Pode ser que precise esperar um pouco. Vou pedir para trazerem algumas bebidas.";
			link.l1 = "Obrigado, Excelência, mas vou recusar. Vou apenas sentar e esperar pelo nosso... amigo em comum.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Capitão, foi sensato da sua parte me procurar. Estamos fazendo todo o possível para combater o comércio ilegal nesta ilha, e realmente valorizo capitães íntegros que buscam fazer negócios pelos meios legais.";
			link.l1 = "Então, quais são os termos e os passos necessários para iniciar o comércio?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "É bastante simples. Para negociar bebidas alcoólicas, você deve pagar um imposto mensal de cem dobrões ao tesouro, manter registros adequados e apresentar relatórios regulares de atividades. Assim que os fundos forem depositados, você poderá começar a negociar de fato.";
			link.l1 = "Excelente. Os termos são perfeitamente razoáveis. Um residente local chamado Christian Deluce irá agir em meu nome. Espero que isso não seja um problema?";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "Como desejar, Capitão. Mas tenha em mente – toda a responsabilidade por seu protegido recairá sobre seus ombros. Se ele cometer alguma falta, você também arcará com as consequências.";
			link.l1 = "Claro. Agradeço pelo esclarecimento, Governador. Faremos os preparativos, e Christian cuidará do pagamento dos impostos.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "Excelente. Fico satisfeito em ver uma postura tão dedicada. Desejo sucesso em sua empreitada.";
			link.l1 = "Muito obrigado. Confio que nossa cooperação trará benefícios à cidade. Até logo.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
