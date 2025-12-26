// Хосе Диос - картограф
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Você quer alguma coisa?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! Me diga, você é Jose Dios, o cartógrafo?";
				link.l3.go = "island";
			}
			link.l1 = "Não, nada.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Sim, sou eu. Não te conheço, señor. O que você quer de mim?";
			link.l1 = "Meu nome é "+GetFullName(pchar)+" e eu fui enviado pelo Jan Svenson. Você se lembra dele?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Ah, senhor Svenson! Claro que me lembro dele! Venha, fique à vontade... Como está o estimado Jan?";
			link.l1 = "Obrigado, ele está bem. Señor Dios, preciso da sua ajuda. Quero consultar você sobre um assunto que deve conhecer bem por causa da sua profissão. Jan me recomendou você como especialista em geografia da região do Caribe...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "Estou ouvindo, senhor. O que você quer saber sobre a geografia do arquipélago?";
			link.l1 = "Dizem que existe uma ilha ou algum outro tipo de formação a noroeste de Havana, entre Cuba e o Golfo do México. Essa ilha nunca foi registrada em nenhum mapa. Gostaria de saber o quão confiáveis são esses rumores.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... Você perguntou sobre algo que me inquieta há muitos anos. Esse lugar que você mencionou já atrai a curiosidade dos geógrafos há muito tempo, mas ninguém jamais teve coragem de explorar aquela região.";
			link.l1 = "Por quê?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "The thing is, that place is some sort of natural anomaly. The probability of storms in that region is much higher than anywhere else. Perhaps the reason lies in the cold sea current, but that's just my hypothesis. Many ships have disappeared there, and that alone was enough to make sailors avoid the area; all the main sea routes pass far from that region anyway.";
			link.l1 = "Imagino que você também não sabe a verdade...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Exatamente, senhor. Mas eu tenho alguns documentos históricos e algumas provas materiais, então tenho todo o direito de suspeitar que há uma grande chance desse lugar realmente existir.";
			link.l1 = "Pode me contar mais?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Certamente. A prova mais importante é um documento histórico com trechos do diário do Capitão Alvarado, que visitou a ilha em 1620. Uma história bastante interessante, posso garantir!";
			link.l1 = "Capitão Alvarado? É a segunda vez que ouço esse nome...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "I am not surprised. The story of Captain Alvarado has been part of folklore for years. It changed, became filled with rumours, lies and dreams, so here it is - the legend of the Island of the Abandoned Ships.\nGossip may change, but paper and ink do not; they remain intact for hundreds of years. Here, read this story - perhaps it will help you uncover what you are looking for.";
			link.l1 = "Obrigado! Tem mais alguma coisa?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "Existe uma teoria de que o fundo do mar naquela região se eleva tanto que forma um enorme banco de areia. E eu já mencionei a correnteza. Segundo relatos de marinheiros, há também uma grande concentração de gaivotas e outras aves marinhas. Alvorado citou os nomes dos navios que faziam parte do esquadrão do almirante Francisco Betancourt, um esquadrão que se perdeu há mais de cinquenta anos. Duvido que isso seja apenas coincidência...";
			link.l1 = "Vou voltar para o meu navio e ler as anotações de Alvarado com atenção. Obrigado pela sua ajuda, Señor Dios!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "You're welcome. Actually, I didn't help you at all; you haven't got the coordinates of the place, and neither have I. I can't even prove that there is an inhabited island out there. But as far as I understand, you intend to explore this area?\nIf so, then be aware that I will be truly grateful for any information, especially if it is supported by material proof. It seems that you are a wealthy man, but I will find a way to repay you.";
			link.l1 = "Ótimo. Então temos um acordo, Señor Dios. Talvez minhas anotações também sejam lidas por alguém no futuro... E quem sabe alguém até escreva uma lenda...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Por que não? Señor "+pchar.name+", vejo que você é um homem aventureiro que viaja bastante, então gostaria de lhe pedir um favor.";
			link.l1 = "Sim? Estou ouvindo.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "Você sabe que sou cartógrafo. Passei dois anos desenhando mapas do arquipélago do Caribe, preparando o atlas do almirante para o concurso do Vice-Rei da Nova Granada. Mas todos os meus vinte e quatro mapas foram roubados da minha casa da maneira mais descarada enquanto eu estava preso por piratas, justamente aqueles dos quais o senhor Svenson me salvou.\nTenho certeza de que o ataque foi organizado por um dos meus concorrentes para se apossar dos meus mapas. Já faz bastante tempo, mas nunca mais vi nenhum dos mapas do meu conjunto desde então.";
			link.l1 = "Entendi. Você quer que eu devolva seus mapas.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Exatamente. Talvez você os encontre em suas futuras aventuras. São fáceis de reconhecer – minha marca está em cada um deles. Se por um milagre você conseguir reunir todos os vinte e quatro mapas, serei generoso em minha recompensa.";
			link.l1 = "Certo. Vou examinar com atenção cada mapa que encontrar no arquipélago daqui pra frente. Bem, preciso ir agora. Obrigado pela conversa interessante e pelo documento.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, é você, señor "+GetFullName(pchar)+"? Tem alguma coisa interessante pra me contar?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"! Senhor Deus, por favor, dê uma olhada no mapa que eu encontrei. Deve ser um dos seus mapas, pelo sinal.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! Senhor Deus, tenho boas notícias para você. Consegui reunir a coleção completa dos seus mapas únicos, exatamente como pediu. Aqui estão todos os vinte e quatro mapas.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"! Sim, estive lá. Eu estava naquele lugar místico sobre o qual conversávamos.";
				link.l4.go = "LSC";
			}
			link.l9 = "Nada por enquanto, senhor. Só queria saber como você está.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Mostre-me... (olhando) Claro! Este é um dos meus mapas para o atlas do almirante! Capitão, preciso pedir que encontre todos eles! Sei que é quase impossível, mas mesmo assim... Não quero perder a esperança.";
			link.l1 = "Não perca isso, senhor. Eu encontrei este mapa, então há uma chance de eu encontrar o resto também. Eles ainda estão no Caribe.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "Seu otimismo realmente me anima, senhor capitão. Talvez eu ainda tenha a chance de mostrar a Dom Juan de Cordova quem é o melhor cartógrafo do arquipélago!";
			link.l1 = "Você vai conseguir superar todos os seus rivais invejosos. Os mapas são realmente incríveis... Adeus, Señor!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "Não acredito no que vejo! Você realmente os encontrou? Todos eles?";
			link.l1 = "Sim. Não foi fácil, mas a sorte realmente sorriu pra mim dessa vez. Pegue suas cartas — são magníficas, cada uma muito melhor do que qualquer outra que já vi.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("You have given the complete set of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "Incrível! Isso é simplesmente inacreditável! Para ser sincero, nunca acreditei que esse momento chegaria.";
			link.l1 = "Dum spiro, spero, Señor Dios. Agora você pode enfrentar Don Cordova. Tenho certeza de que ele vai valorizar muito seus talentos.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "Tenho que lhe agradecer, capitão! Você nem imagina o quanto me ajudou. E como prometi, vou recompensá-lo. Também tenho um presente para você. Acho que, como marinheiro, vai achar muito útil.";
			link.l1 = "Você me deixou intrigado, senhor!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "Aqui! Este é um telescópio naval de minha própria criação. É único, você não vai encontrar outro igual em nenhum lugar. As lentes foram feitas na Europa pelo mestre mais habilidoso da Espanha. O estojo foi feito por um armeiro amigo meu. Um tripé especial vai te ajudar a mirar o aparelho mesmo com o balanço do navio. Com ele, você enxerga tudo o que precisa, seja um navio ou um forte.";
			link.l1 = "Que presente maravilhoso! Muito obrigado, Señor Dios.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Use, senhor capitão. Espero que meu telescópio lhe seja útil.";
			link.l1 = "Sem dúvida! Mal posso esperar para instalar isso no convés do meu navio e dar uma olhada através dele.";
			link.l1.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "Além disso, já que as coisas acabaram assim, tenho outra pequena proposta para você.";
			link.l1 = "O que foi? Estou ouvindo com toda atenção.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "Me ocorreu que esses mapas são excelentes para um explorador, mas não oferecem tudo o que um capitão de navio precisa. Veja só: todas as baías, cabos e lagoas estão desenhados com grande precisão, mas não dá para traçar uma rota entre as ilhas usando eles.";
			link.l1 = "É verdade, com eles você não consegue navegar.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "Mas eu também posso fazer um mapa do arquipélago para você! E não é daqueles que você compra da Companhia Holandesa das Índias Ocidentais, mas um mapa único, de primeira.";
			link.l1 = "Obrigado, senhor Dios, mas não preciso de um mapa assim. Ainda assim, agradeço muito pela oferta!";
			link.l1.go = "best_map_02";
			link.l2 = "Está brincando?! Señor Dios, como eu poderia recusar? Só me diga o que precisa - não vou poupar dinheiro nem ferramentas!";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "Bem, eu tinha que oferecer. De qualquer forma, foi um prazer fazer negócios com você, señor "+pchar.lastname+"!";
			link.l1 = "Igualmente! Boa sorte pra você!";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "Já tenho os instrumentos, obrigado. Vou precisar de um mapa padrão do arquipélago, além de uma bússola e um cronômetro certificado — o mapa precisa ser preciso, caso contrário seria sabotagem. E como pagamento — um baú de dobrões.";
			if(CheckAMapItems())
			{
				link.l1 = "Já tenho tudo o que você mencionou comigo. Aqui, pode pegar.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "Um mapa padrão do arquipélago, uma bússola, um cronômetro certificado e um baú de dobrões. Entendido! Vou entregar tudo assim que puder — me espere!";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "Saudações, meu caro amigo! Trouxe o mapa padrão do arquipélago, a bússola, o cronômetro certificado e o baú de dobrões?";
			link.l1 = "Ainda não, Señor Dios. Mas eu vou, prometo!";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "Sim, Senhor Deus. Aqui, está tudo aqui — pode pegar.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("You handed over a regular map of the archipelago, a boussole, a tariffed chronometer, and a chest with doubloons.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "Então, vou começar a trabalhar. Volte daqui a uma semana, e prometo que não vai se arrepender!";
			link.l1 = "Não tenho dúvidas, senhor. Até daqui a uma semana!";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "Ah, senhor "+pchar.lastname+", aí está você! Fico feliz em informar que terminei o mapa do arquipélago! E ouso dizer, está muito melhor do que o que você me deu.";
				link.l1 = "Meu amigo... Este mapa está incrível! Eu diria que é uma obra-prima! Como posso te agradecer por tudo o que fez por mim?";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "Saudações, senhor! Preciso pedir desculpas, mas o mapa ainda não está pronto.";
				link.l1 = "Sim, lembro que você precisava de uma semana. Só vim ver como você está.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "Ah, deixe disso, meu amigo. Foi um prazer criar um mapa desses para um capitão nobre que sabe realmente apreciá-lo. Ah, e aqui está o seu mapa original de volta também. Que os mares lhe sejam favoráveis!";
			link.l1 = "Muito obrigado! Você tem razão — este mapa realmente não tem preço para mim. Adeus, Señor Dios!";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("You received an excellent archipelago map!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "Sério?! Você encontrou? Fique à vontade, acho que a conversa vai demorar um pouco, não é?";
			link.l1 = "Eu realmente tenho muito para te contar sobre a ilha. Mas antes, quero que me prometa uma coisa. Vejo que você é um homem de honra, então tenho certeza de que vai cumprir sua palavra...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "Do que está falando, Capitão?";
			link.l1 = "Tem gente morando lá... e eles não vão gostar nada se alguém se meter na vida deles. Duvido que a possível chegada de um esquadrão de 'pesquisa' seja bem recebida.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "Então quero que me dê sua palavra de honra de que não vai divulgar nenhuma informação que possa ser usada para encontrar a Ilha nos próximos dez anos após nossa conversa. Pode publicar qualquer informação sobre os habitantes, suas vidas e tudo mais, só não revele a localização da ilha.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "Concordo, Capitão. Dou-lhe minha palavra de nobre que não contarei a ninguém nem a localização da Ilha, nem qualquer informação que possa prejudicar seus habitantes pelos próximos dez anos.";
			link.l1 = "Então ouça minha história. Pode até anotar, se quiser. Veja bem, a Ilha é formada por muitos navios naufragados, cujos cascos estão espalhados por um grande banco de areia...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "Incrível! Você me trouxe informações muito valiosas, capitão! Os descendentes do almirante de Betancourt estão vivendo na ilha! Agora sabemos o que aconteceu com o esquadrão dele. E há um ponto a menos em branco no mapa do arquipélago do Caribe... Muito obrigado pelo seu relato, "+pchar.name+"!";
			link.l1 = "Agora você entende por que pedi tanto cuidado ao contar o que te falei?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "Entendo. Pode ter certeza de que vou cumprir minha palavra. Me diga... você tem algum bem material da Ilha?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "Eu tenho instruções de navegação para a Ilha dos Navios Abandonados. Aqui, dê uma olhada. Elas permitem que você conduza um pequeno navio pelos recifes e destroços e atraque em segurança na Ilha. É impossível chegar à Ilha sem essas instruções.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Infelizmente, não tenho nenhum.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "(olhando) Que documento excelente! Foi feito por um homem habilidoso em cartografia. Nem eu teria feito melhor. Incrível! Capitão, por que não me entrega essas instruções de navegação? Uma história é uma história, mas este papel precisa ser mostrado aos geógrafos mais renomados do Velho Mundo!";
			link.l1 = "Senhor Deus, infelizmente, preciso deste documento para mim. Como já disse antes, é impossível atravessar os recifes que cercam a ilha sem ele. Mas você pode fazer uma cópia das instruções, se quiser, e ficarei muito contente se também tiver uma com você.";
			link.l1.go = "LSC_10";
			//link.l2 = "Senhor Deus, infelizmente, preciso deste item para mim. Como já disse, é impossível contornar os recifes ao redor da ilha sem ele. Eu o sacrificaria em nome da ciência, mas... Tenho certeza de que você entende.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Com certeza. É seu direito, embora seja uma pena... De qualquer forma, obrigado pela sua história! Você prestou um grande serviço a geógrafos, cartógrafos e outros curiosos.";
			link.l1 = "De nada, senhor. Bem, preciso ir agora. Até logo.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "Que pena... De qualquer forma, obrigado pela sua história! Você prestou um grande serviço a geógrafos, cartógrafos e outros curiosos.";
			link.l1 = "De nada, senhor. Bem, preciso ir agora. Até logo.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Claro, "+pchar.name+". Você dedicou muito do seu tempo para mim. Envie minhas saudações ao Señor Svenson!";
			link.l1 = "Adeus, Senhor Dios.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Muito obrigado! Que gentileza sua. Me dê um instante...";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Muito obrigado! Foi muita gentileza sua. Agora temos não só um testemunho, mas também uma prova material... Não vou deixar de te recompensar, Capitão. Tenho um pequeno presente para você.";
			link.l1 = "Que tipo de presente?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Eu sou apaixonado não só por cartografia e geografia, mas também por matemática e astronomia. Passei um ano tentando criar uma ferramenta universal para determinar latitude e longitude. E consegui algum progresso. Veja só:\nEste é meu sextante. Eu mesmo o projetei. O problema é que ele não funciona. Ele exige um cronômetro extremamente preciso. Mesmo os feitos pelos melhores artesãos acabam apresentando erros inaceitáveis com o tempo. Por isso, minha ferramenta não serve para nada por enquanto.\nMas como você viaja bastante, talvez encontre um cronômetro preciso o suficiente para que o sextante funcione. Assim que encontrar um relógio desses, você não vai mais precisar de bússola, astrolábio, ampulhetas ou qualquer outro cronômetro duvidoso—minha ferramenta vai substituir todos eles.";
			link.l1 = "Obrigado, Señor Dios. Vamos torcer para que eu encontre um cronômetro que faça sua invenção funcionar. Eu gostaria de ter um aparelho desses... em perfeito estado. Bem, preciso ir agora. Adeus.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é "+GetSexPhrase("um ladrão, hein! Guardas, peguem-no","uma ladra, hein! Guardas, prendam ela")+"!!!","Eu não acredito nisso! Virei de costas por um segundo – e você já está mexendo nas minhas coisas! Pare, ladrão!!!","Guardas! Roubo! Peguem o ladrão!!!");
			link.l1 = "Aaaah, diabo!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}