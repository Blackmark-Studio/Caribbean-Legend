// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que deseja saber?","Acabamos de falar sobre isso. Você deve ter esquecido...","É a terceira vez hoje que você traz essa pergunta...","Você está se repetindo como um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, é mesmo a terceira vez...","É...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Por acaso o Francois Gontier passou pela sua cidade? Ele tem uma corveta '"+pchar.questTemp.Slavetrader.ShipName+"', só por precaução... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Me diga, amigo, onde posso encontrar Don Diego de Montoya? Cheguei tarde? Ele já partiu para o continente?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Escute, um homem chamado Joachim Merriman passou por aqui? Um médico de meia-idade, português, com bigode, barba imperial e olhos penetrantes? Talvez ele tenha procurado um quarto para alugar?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "Aha, aquele sujeito sombrio? Sim, ele já passou por aqui. Vou te contar uma coisa: ele tinha um encontro com Oregon-e-Haskon. Pediu uma licença. Mas não deu certo pra ele e foi embora.";
			Link.l1 = "E para onde ele foi, você sabe? Estou atrás dele desde Porto Bello e simplesmente não consigo encontrá-lo.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "What do you need from him? He's afraid of outsiders, always hiding from everyone; as soon as he sees an armed stranger, he grabs his sword. He only walks around surrounded by four guards. Are you, by any chance, the one he's so wary of?";
			Link.l1 = "Senhor, as pessoas vivem repetindo isso! O que foi, eu pareço um assassino? Ele é um velho amigo meu, só estou com pressa pra lhe dar umas notícias. Ele vai ficar bem feliz em saber que não precisa mais se esconder—ninguém está atrás dele.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "Não precisava se esconder? Ha-ha-ha! Um dia antes de partir de Havana, uma turma inteira de bandidos tentou matá-lo na selva... Claro, ele estava com seus próprios homens, e eles transformaram os atacantes em carne moída num instante. E agora você vem dizer...";
			Link.l1 = "Ah, deixa disso. Devem ter sido só uns bandidos locais tentando roubar a carteira dele. Você mesmo sabe quantos canalhas andam vagando pela selva. Então, pra onde ele foi?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Bem, depois que ele foi mandado para longe da residência por um bom tempo, ficou insistindo que ia se entregar para os come-sapo, para os conterrâneos dele. Partiu para Tortuga, para algum tal de d'Ogeron... Também resmungou algo sobre a amante dele, mas não consegui entender direito.";
			Link.l1 = "Então, Tortuga? Excelente! Espero encontrá-lo por lá. Obrigado, "+npchar.name+", você foi de grande ajuda. Tchau.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Hm... E por que um francês estaria interessado no Don Diego, hein?";
			link.l1 = "O fato de eu ser francês não importa. O que interessa é este documento assinado pelo Inquisidor. Veja só... está vendo agora? Tenho uma mensagem urgente para Diego.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A-ha, então você trabalha para Sua Reverência, Padre Vincento? Isso muda as coisas. Don Diego de Montoya partiu há dois dias com seu esquadrão, mas logo voltou em seu lugre-correio. Um dos navios dele naufragou nos recifes ao sul de Cuba, então ele passou o dia comprando materiais para reparo\nVá até a baía ao sul, você vai encontrar um navio lá e o próprio homem. Duvido que já tenham conseguido consertar os buracos.";
			link.l1 = "Obrigado, amigo! Você foi de grande ajuda!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "De jeito nenhum, a qualquer hora. Sempre fico feliz em ajudar um irmão jesuíta.";
			link.l1 = "Sim, pax vobiscum e tudo mais.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "O diabo sabe, camarada. Ele pode até ter chegado, mas eu não fiquei sabendo. Desculpe.";
			link.l1 = "Entendo. Que pena. Vou continuar minha busca...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
