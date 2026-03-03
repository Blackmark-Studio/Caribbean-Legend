// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"O que foi, "+GetAddress_Form(NPChar)+"...","Esta já é a terceira vez que você me incomoda...","Mais perguntas, imagino?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar a minha memória...","Sim, é mesmo a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Estou procurando meu velho camarada Fernand Luc. Tenho umas perguntas pra ele. Ouvi dizer que ele aprontou por aqui semana passada...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Meu amigo e eu combinamos de nos encontrar aqui, mas não o vejo em lugar nenhum. Você sabe para onde ele foi? Ele ainda está na cidade, ou pelo menos na ilha? O nome dele é Longway – ele é chinês.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l2 = "Boas notícias, "+npchar.name+". Eu tenho exatamente o que vai salvar a sua situação. Cem garrafas de vinho excelente e cem garrafas de rum. Com essa carga, seus clientes vão voltar a se afogar em rios de bebida. Está pronto para pagar?";
				link.l2.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l2 = "Então, "+npchar.name+", está pronto para discutir os termos do acordo?";
				link.l2.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l2 = "Então, "+npchar.name+". Da minha parte, está tudo certo e as mercadorias já estão a caminho da taverna. Podemos seguir com o pagamento?";
				link.l2.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Talvez ele ainda esteja se divertindo no inferno. Seu amigo está morto, então você chegou um pouco tarde, capitão. Aquele homem ali, sentado na mesa mais afastada, pagou pelo enterro dele, embora eu tenha a impressão de que foi ele mesmo quem causou tudo isso. Dizem que ele tem cara de enforcado. O nome dele é Robert Martene. Se quiser, pode ir lá e perguntar pessoalmente. ";
			link.l1 = "Obrigado, amigo. Vou lá conversar com o Monsieur Robert. Vamos beber pela alma do velho Luc, que ele descanse em paz...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "O que há para discutir? Ele atacou você e seu amigo, vocês revidaram, vejo isso quase todo dia. Bom trabalho. Agora só preciso limpar essa bagunça...";
			Link.l1 = "Você vai limpar isso, imagino que já esteja acostumado. O que você sabe sobre ele?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Na verdade, não muito. Ele apareceu aqui há alguns dias. Gostou do lugar, até alugou uma casa nos arredores da cidade. Vinha sempre, pagava certinho. E, o mais importante, sempre se comportou bem, nunca falou uma palavra ruim pra ninguém. Ainda estou chocada que ele atacou você e seu amigo.   Achei que ele fosse se estabelecer aqui de vez.";
			Link.l1 = "De certa forma, sim. Bem, não é muito, mas obrigado por isso, meu amigo. Até mais.";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_BasTerTavern_3");
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Esse nome não me diz nada, e geralmente, não deixo pessoas como ele entrarem no meu estabelecimento, nem me interesso por elas.";
			Link.l1 = "Justo. Certo, até mais tarde.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", é ainda pior do que isso. Meu fornecedor de Antígua perdeu a destilaria — piratas atacaram, queimaram tudo até o chão. Agora ele diz que não devemos esperar rum ou vinho por pelo menos dois meses.";
			link.l1 = "Então arrume um novo fornecedor. Você não vai ficar aí parado esperando dois meses, vai?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Encontrar um fornecedor confiável não é fácil. Tentei negociar com pequenos comerciantes, mas eles não são confiáveis. Às vezes as mercadorias chegam, às vezes não. Com um grande fornecedor, tudo funciona como um relógio — entregas estáveis e alta qualidade.";
			link.l1 = "Bem, se os fornecedores normais estão dando problema, talvez você devesse procurar alguém nas sombras? Eles raramente falham, e as mercadorias estão sempre disponíveis.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Você entende, "+GetAddress_Form(NPChar)+", esta taverna está sob vigilância pública. Não quero nenhum problema com as autoridades. Se alguém com boa reputação trouxesse as mercadorias, eu não só compraria um lote, como também fecharia os olhos para a procedência\nAfinal, numa situação tão difícil, quem liga para esses detalhes? O principal é não levantar suspeitas. Mas, a longo prazo, só faço negócio com comerciantes sérios e honestos.";
			link.l1 = "Entendo. Bem, talvez eu volte mais tarde. Qualquer problema pode ser resolvido com um pouco de criatividade.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Capitão, isso é incrível! Como você conseguiu isso? Não importa, de verdade. Só me diga, o que você quer em troca de uma remessa tão luxuosa de bebida? E a papelada, vai estar toda em ordem?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Documentos? Claro que está tudo perfeitamente em ordem. Você não vai mesmo querer conferir, vai?";
				link.l1.go = "TPZ_Tavern2_2";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				link.l1 = "Documentos?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				Notification_Reputation(false, 40, "low");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Capitão, por favor, entenda, é fundamental para mim receber essa remessa de álcool. Mas minha liberdade e reputação são tão valiosas quanto. O governador é implacável com quem negocia no mercado negro, até com os menores. Se as pessoas falassem bem de você, eu poderia ignorar a falta de documentos, mas agora... você está chamando atenção demais, e não da boa...";
			link.l1 = "Parece que é hora de fazer algumas boas ações. Espere por mim, eu volto já.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "Desta vez, acho que vou confiar na sua palavra. Então, quanto você quer pelo lote?";
			link.l1 = "Quero trinta doblões para cada dez garrafas de vinho, e cinco doblões para cada dez garrafas de rum. O lote completo — cem garrafas de cada — vai te custar trezentos e cinquenta doblões.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Espere aí, Capitão! Isso é um roubo à luz do dia! Sim, minha situação é desesperadora, mas não vou tocar meu negócio no prejuízo!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Talvez eu possa te dar um desconto. Mas não é só isso. Quero ser seu fornecedor fixo. Garanto entregas rápidas e sem complicações. Vou alugar um armazém em Basse-Terre, e você vai receber sua mercadoria direto de lá, sem atrasos. Sempre vai ter bebida suficiente armazenada para evitar qualquer falta. Com o desconto, o preço fica em duzentos e quarenta dobrões. O que me diz?";
				link.l1.go = "TPZ_Tavern2_4";
				Notification_Skill(true, 50, SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Certo, estou disposto a baixar o preço para duzentos e quarenta dobrões por carregamento — estou buscando uma parceria de longo prazo. No futuro, posso atender todas as suas necessidades e garantir um fornecimento confiável. O que me diz?";
				link.l1.go = "TPZ_Tavern2_7";
				Notification_Skill(false, 50, SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "Isso ainda é mais do que eu costumava pagar. Mas aprendi minha lição — estabilidade vale o preço. Aceito seus termos, mas saiba disso: um deslize, e arrumo outro fornecedor. Preciso entender pelo que estou pagando a mais. E mais uma coisa — como você pretende lidar com as autoridades?";
			link.l1 = "Vou cuidar disso agora mesmo. Assim que tudo estiver resolvido, volto com a mercadoria.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Por favor, não demore. Mal posso esperar para ver as canecas dos meus clientes cheias de novo.";
			link.l1 = "Não se preocupe, não vou te deixar esperando.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "Ainda está caro demais, Capitão. Esse preço é mais alto do que eu pagava ao meu fornecedor anterior. Mesmo que eu aceite agora, daqui a alguns meses vou ter que voltar para ele assim que a produção voltar ao normal. Não vejo motivo para pagar a mais.";
			link.l1 = "Entendi. Tudo bem. Minha oferta final — duzentos dobrões. Se isso não for suficiente, então não faz sentido continuar essa conversa.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Certo, combinado. Duzentos está aceitável. Mas me diga, como você pretende lidar com as autoridades da ilha? Como eu disse antes, o governador vigia de perto a ilha por causa do contrabando. Ele não vai tolerar negócios acontecendo bem debaixo do nariz dele.";
			link.l1 = "Ha-ha, bem, eu discordaria disso. Mas pode ficar tranquilo — pretendo resolver toda a burocracia rapidinho.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Por favor, não demore. Mal posso esperar para ver as canecas dos meus clientes cheias de novo.";
			link.l1 = "Não se preocupe, não vou te deixar esperando.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Claro, Capitão! Então, quanto você quer pela sua carga?";
				link.l1 = "Por cada dez garrafas de vinho eu quero trinta dobrões, e cinco dobrões para cada dez garrafas de rum. A carga toda — cem garrafas de cada — vai te custar trezentos e cinquenta dobrões.";
				link.l1.go = "TPZ_Tavern2_3";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				dialog.text = "Me desculpe, Capitão, mas sua reputação ainda deixa muito a desejar.";
				link.l1 = "Droga...";
				link.l1.go = "exit";
				Notification_Reputation(false, 40, "low");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Claro, Capitão, claro! 240 doblões, conforme combinado. Aqui está!";
				link.l1 = "Foi um prazer fazer negócios com você! Agora a taverna vai voltar a transbordar de rum e vinho.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Claro, Capitão, claro! 200 doblões, conforme combinado. Aqui está!";
				link.l1 = "Foi um prazer fazer negócios com você! Agora a taverna vai voltar a transbordar de rum e vinho.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "Você é meu salvador, Capitão! Vou esperar entregas parecidas a cada duas semanas. Espero que cumpra suas obrigações direitinho. Se acontecer outra seca dessas, minha taverna não vai aguentar...";
			link.l1 = "Não precisa se preocupar, "+npchar.name+". Meu representante na cidade é Christian Deluce. Ele vai garantir que sua taverna nunca fique sem vinho ou rum.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian? Eu conheço ele. Um homem responsável, embora... bem, deixa pra lá. Já que você resolveu as coisas com as autoridades, acho que posso confiar nele.";
			link.l1 = "Excelente. Agora, se me dá licença, tenho mais um assunto para resolver nesta cidade.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Venha nos visitar mais vezes!";
			link.l1 = "Com certeza, farei isso.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
