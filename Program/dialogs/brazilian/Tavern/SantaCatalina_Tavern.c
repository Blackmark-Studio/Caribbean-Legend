// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Claro, Helen. O que foi?","Ah, finalmente lembrou o que queria?","Tem certeza de que está bem? Você está começando a me preocupar. Talvez devesse procurar um médico? ","Certo, Helen. Vai descansar um pouco, pega um ar fresco – enfim, dá uma pausa. Depois volta. Tá bom?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Não, nada de mais.","Não, não, desculpe incomodar.","Você provavelmente está certo...","Sim, você provavelmente está certo. Isso é o melhor a se fazer.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","No decorrer deste dia inteiro, essa já é a terceira vez que você faz essa pergunta...","Mais perguntas, imagino?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Hum, onde foi parar minha memória...","Sim, realmente é a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Escute, "+npchar.name+", quem é Jan Svenson, e como posso encontrá-lo?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Escuta, chegou algum alquimista na cidade, um médico? Ele é italiano, tem uns trinta anos, se chama Gino Gvineili. Você ouviu falar dele?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "É a primeira vez que encontro alguém que não sabe quem é o Diabo da Floresta. Esse apelido foi dado a ele pelos espanhóis, que ofereceram um saco inteiro de ouro pela cabeça daquele corsário de Ilha da Providência, já faz uns quinze anos! Pois é, o tempo voa... O povo já começou a esquecer do nosso Jan. Talvez esteja mesmo na hora dele descansar.";
			link.l1 = "Acabei de chegar aqui e ainda não sei muita coisa...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Se você se interessa pelo passado, posso te vender um livro de história. Muitos pagariam uma fortuna por ele, mas eu...";
			link.l2 = "Não me venha com rodeios! Eu te fiz uma pergunta. Vou repetir: onde mora Jan Svenson? Tenho um assunto sério para tratar com ele.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Ele mora numa mansão em frente à casa do nosso prefeito, ao lado da fonte. Mas, no momento, ele está passando por uma fase difícil e eu não recomendaria incomodá-lo, a menos que seja realmente muito importante.";
			link.l1 = "Por quê?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "A garota preferida dele, Helen, também conhecida como Rumba, filha do seu falecido amigo Shawn McArthur, desapareceu. Que descanse em paz, velho... Jan trata a jovem endiabrada como se fosse sua própria filha, já que não tem filhos. Mas a garota sumiu junto com sua escuna 'Rainbow' e toda a tripulação\nTenho pena da garota. Uma beleza rara, e ainda por cima esperta. Temperamental e intensa como fogo, por isso a chamavam de Rumba! O pai dela ensinou tudo o que sabia, ela herdou o navio e cada membro da tripulação ficou ao lado dela. Até os lobos-do-mar mais velhos a reconheceram como capitã...";
			link.l1 = "Uma pirata? O que será que aconteceu com ela?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Quem sabe... Uma semana não é tanto tempo assim, mas a viúva de MacArthur está certa de que algo aconteceu com a filha dela, e conseguiu convencer Svenson disso. Ele chamou seus homens e começou a procurar pessoalmente, mas até agora sem resultado. O 'Rainbow' e sua tripulação simplesmente desapareceram\nPosso te dizer onde encontrar a Gladys por mil peças de oito.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "Seu conhecimento custa caro, mas você conseguiu despertar meu interesse. Aqui está o seu dinheiro. Onde posso encontrá-la?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Não. Eu mesmo resolvo se for preciso. Tchau, obrigado pela história!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "A casa dela fica ao lado do píer, à esquerda do ancoradouro. Mas provavelmente ela não está lá. Passa o dia inteiro rondando as muralhas do forte, de olho na filha querida. Já deve ter chorado até não aguentar mais.";
			link.l1 = "Obrigado pela história! Até logo, amigo!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Não, nunca ouvi falar. Temos herbalistas e médicos, mas ninguém com esse nome.","É a primeira vez que ouço um nome tão estranho. Não, nunca tivemos uma visita do homem de quem você fala.","Nem temos alquimistas aqui, de jeito nenhum. Temos médicos, mas nenhum com um nome estranho desses.");
			link.l1 = "Entendi. Que pena. Vou continuar procurando!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
