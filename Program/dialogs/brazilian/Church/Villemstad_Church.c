// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("meu filho","minha filha")+"?","Pode perguntar, estou ouvindo..."),"Estou ouvindo, pode falar. "+GetSexPhrase("meu filho","minha filha")+"...","Pela terceira vez, "+GetSexPhrase("meu filho","minha filha")+", peça o que precisar.","Um clérigo tem muito trabalho e você está me distraindo, "+GetSexPhrase("meu filho","minha filha")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não, padre..."),"Não tenho nada a dizer, me desculpe.","Eu vou perguntar, mas depois. Me perdoe, padre.","Com licença, padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "Com licença, padre, um dos clérigos da sua paróquia me pediu para investigar a casa onde Joachim Merriman estava alugando um quarto...";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "E então? Você já esteve lá, meu filho?";
			link.l1 = "Sim, eu fui. Mas, sinceramente, teria sido melhor se eu não tivesse ido. Fui atacado por um esqueleto com um machado enorme no quarto de cima. Consegui sair vitorioso, embora não tenha sido nada fácil.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Meu Senhor, tenha piedade de nossas almas! Meus piores temores se tornaram realidade!";
			link.l1 = "Isso não é tudo, padre. Quando finalmente acabei com aquilo, soltou um grito que parecia de mulher. Vasculhando os ossos, encontrei algumas joias, então é seguro supor que era a dona da casa desaparecida.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(faz o sinal da cruz)... Pobre serva de Deus, que o Senhor conceda descanso à sua alma...";
			link.l1 = "Parece que Merriman é mesmo um feiticeiro. Não faço ideia de como alguém conseguiria transformar um homem vivo numa aberração dessas.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman é um feiticeiro muito temido, meu filho. Eu o conheci na Europa, mas naquela época ele não era capaz de nada parecido. Aqui, no Caribe, ele conseguiu algo que lhe deu poderes sobrenaturais.";
			link.l1 = "O senhor conhecia o Merriman, padre?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That I did. Back then I was just a humble priest in one of Lisbon's parishes. Joachim Merriman was a wealthy nobleman, and at some point he became interested in old manuscripts and scrolls brought by sailors from distant lands. He also began to study alchemy, but after some time he went into seclusion.\nPeople saw flashes of light in his house; sometimes they could also smell something strange. Then they saw him in the cemetery at nights. Once they saw him digging out a fresh corpse and bringing it to his home. And when patience ran out, local father superior contacted the Inquisition.\nWhen the guards breached the door of Merriman's house, Joachim was not there - he had escaped through a secret passage. They found a lab in the basement, and even the seasoned soldiers were shocked and sickened by what they saw. Whole rotting and dismembered bodies, human and animal skeletons, strange things... Fear and hatred for Merriman was so significant that his house was demolished in an instant.\nMerriman disappeared without a trace. The Inquisition began to search for him, sentencing him in his absence to burn at a stake as a dangerous warlock. But they never found him. And now, after all these years, I saw him again on the streets of Willemstad.";
			link.l1 = "Por que você não contou aos inquisidores?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Meu filho, você não sabe que nossa igreja está em conflito com a Inquisição? Eu prefiro manter distância do Padre Vincento e daqueles brutamontes.";
			link.l1 = "Entendo. Padre, acho que descobri de onde Merriman tirou seu poder. Ele conseguiu um artefato antigo, um crânio de jade de Yum Cimil, um antigo deus da morte adorado pelos índios da tribo Chavin.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Hm, Merriman era conhecido por realizar rituais de feitiçaria e experimentos com cadáveres, então isso pode muito bem ser verdade. Agradeço a Deus por esse homem terrível ter deixado Willemstad e por você ter destruído as sementes demoníacas que ele tentou plantar aqui. Somos profundamente gratos a você, meu filho. Por favor, aceite estes itens sagrados como sua recompensa.";
			link.l1 = "Obrigado, padre";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "Mas isso não foi o fim dos nossos problemas, meu filho. Recentemente, recebi uma carta de "+sld.name+", padre superior da igreja em Havana. Ele traz notícias terríveis. Em uma caverna na selva cubana, caçadores viram abominações assustadoras, mortos que caminham. E isso é ainda mais preocupante, considerando que recentemente pessoas desapareceram depois de se aventurarem na selva.";
			link.l1 = "Hum... você está sugerindo que isso também é obra do Merriman?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Eu não sei o que pensar, meu filho. Mas se aquele bruxo negro ficou tão poderoso, todos os habitantes do arquipélago estão em grande perigo. Só Deus sabe o que esse servo do diabo pode estar tramando\nEspero mesmo que o padre "+sld.name+" estava errado, mas de qualquer forma - por favor, vá até Havana e converse com ele. Preparei uma licença de comércio para você, válida por um mês. Com ela, você poderá entrar no porto de Havana sem dificuldades.";
			link.l1 = "Certo, padre. Vou para Havana.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Eu não sei o que pensar, meu filho. Mas se aquele bruxo negro ficou tão poderoso, todos os habitantes do arquipélago correm um grande perigo. Só Deus sabe o que esse servo dos demônios pode estar planejando.\nEspero mesmo que o Padre "+sld.name+" estava errado, mas não importa – peço que viaje até Havana e fale com ele.";
			link.l1 = "Claro, padre. Vou para Havana imediatamente.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Fico feliz que você seja um verdadeiro filho da Igreja. Rezarei pela sua saúde e bem-estar dia e noite. Vá com a minha bênção. Que o Senhor te fortaleça na sua luta contra esses poderes profanos.";
			link.l1 = "Obrigado, e adeus, Padre.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
			AddLandQuestMark(characterFromId("Havana_Priest"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
