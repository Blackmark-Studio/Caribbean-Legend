int iLoxlyPseudoGlobal;

// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Meu nome é Albert Loxley e sou advogado. Defendo os interesses dos meus clientes nos tribunais. Meus serviços são caros, mas valem cada centavo, pode ter certeza.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "Estou com problemas com as autoridades inglesas.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "Estou com problemas com as autoridades francesas.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "Estou com problemas com as autoridades espanholas.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "Estou com problemas com as autoridades holandesas.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Briguei com os contrabandistas.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Obrigado, mas felizmente ainda não precisei dos serviços de um advogado.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
					break;
				}
				link.l1 = "Obrigado, mas felizmente ainda não precisei dos serviços de um advogado.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "I need your services. I am an authorised delegate of a young lady named Helen McArthur; she is the granddaughter of the famous Nicolas Sharp. She is the only heir at law left after the death of her mother and uncle. She has every right to Isla Tesoro according to her uncle's testament. How much would you ask for helping Helen become the rightful mistress of the island?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "O senhor precisa dos meus serviços? Garanto que ficará satisfeito.";
						link.l1 = "Yes, I need them. I am an authorised delegate of a young lady named Helen McArthur; she is the granddaughter of the famous Nicolas Sharp. She is the sole heir at law after the death of her mother and uncle. She holds all rights to Isla Tesoro according to her uncle's testament. How much would you ask for helping Helen become the rightful mistress of the island?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Senhor, ainda não estou a par dos detalhes do seu negócio. Por favor, venha me procurar mais tarde, como já lhe disse.";
						link.l1 = "Certo.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Senhor, infelizmente, preciso de mais tempo para reunir todos os documentos necessários nos arquivos. Ainda não estou pronto. Por favor, volte mais tarde.";
						link.l1 = "Certo.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Senhor, por que você está trabalhando tão devagar?! Acabou para o seu patrão. O prazo para validar o testamento expirou, e Isla Tesoro agora pertence à Inglaterra. Logo vai virar uma base militar.";
							link.l1 ="Mas que droga! Parece que todo o meu esforço foi em vão...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Ah, aqui está você, senhor. Já me familiarizei com os materiais, então está na hora do adiantamento. Trouxe os dobrões com você?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Sim, eu tenho. Aqui estão seus dobrões.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Perdoe-me pela minha memória fraca, deixei-os em um baú no meu navio. Vou trazê-los imediatamente.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Senhor, por que você está trabalhando tão devagar?! Já era para o seu patrão. O prazo de validação do testamento acabou e Isla Tesoro agora pertence à Inglaterra. Em breve vai virar uma base militar.";
							link.l1 ="Que droga! Parece que todo o meu esforço foi em vão...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Senhor, conseguiu encontrar algo que possa provar a ascendência do seu patrão?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Ainda não. Mas estou trabalhando nisso.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Sim. Eu realmente tenho provas irrefutáveis.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "A-ah, aqui está você, senhor. Que bom vê-lo. Admito que já estou esperando há um bom tempo. Este é o seu principal?";
						link.l1 = "Sim. Deixe-me apresentar você à Helen McArthur.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Precisa dos meus serviços, senhor? Garanto que ficará satisfeito.";
					link.l1 = "Obrigado, mas não preciso delas agora.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Bom dia, senhor. Imagino que tenha trazido meu pagamento?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Sim, eu tenho. Aqui estão seus dobrões.";
						link.l1.go = "saga_36";
					}
					link.l2 = "Sabe, senhor Loxley, eu pensei... O que quero dizer é que 900 doblões é mais do que suficiente pelo seu trabalho.";
					link.l2.go = "saga_38";
					link.l3 = "Eu me lembro, senhor Loxley. Vou trazer isso daqui a pouco...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Precisa dos meus serviços, senhor? Garanto que ficará satisfeito.";
				link.l1 = "Obrigado, mas não preciso delas agora.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Senhor, o senhor deve ter passado tempo demais no mar. Isla Tesoro agora é uma base militar da Marinha Inglesa! Sim, o testamento de Sharp existe, mas já perdeu a validade e Isla Tesoro virou propriedade da coroa inglesa. Que pena!";
				link.l1 ="Por todos os deuses! Parece que todo o meu esforço foi em vão...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "A dama afirma ser dona da ilha inteira? Hm... Parece que isso não vai ser fácil. Isla Tesoro já é quase uma colônia inglesa...";
				link.l1 = "Ainda não. Segundo o testamento, o homem ou a mulher que apresentar as duas partes do mapa se tornará o dono da Isla Tesoro. Nós temos as duas partes do mapa de Sharp, que é a principal prova de herança.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... Muito bem. Preciso ir ao arquivo e me inteirar dos materiais relacionados à Isla Tesoro. Você está com o mapa?";
			link.l1 = "Eu tenho, mas só vou te entregar depois que assinarmos um contrato. Então, qual seria o preço pelos seus serviços?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "Como eu disse - não vai ser fácil. Você precisa provar o direito de posse de uma ilha inteira, não de um barco velho ou de uma cabana. Além disso, Nicolas Sharp era pirata, e ajudar piratas ou seus parentes sai caro."+sTemp;
			link.l1 = "Você vai me dizer o valor exato?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Senhor, o valor final será definido durante o julgamento. Ainda não sei o quão complicado isso vai ser. Mas estou pronto para calcular um adiantamento - "+sTemp+" dobrões. Esse valor em ouro terá que ser pago novamente uma ou duas vezes, dependendo de como nossos negócios vão.\nTraga o dinheiro em uma semana, preciso de tempo para verificar os arquivos e me preparar. Depois faremos um acordo. Combinado?";
			link.l1 = "Disseram que você é o melhor advogado do arquipélago, então temos um acordo. Nos vemos em uma semana!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Muito bem. Estou pronto para assumir seu caso e defender seus interesses no tribunal. Agora, vamos direto ao ponto. Me saí bem nos arquivos e conversei com pessoas importantes. O caso da herança de Sharp não vai ser fácil. Ainda bem que você conseguiu as duas partes do mapa. Mas isso talvez não seja suficiente.\nO coronel Doyle tem grandes planos para Isla Tesoro, já que não conseguiu tomar o controle de Tortuga. A ilha tem defesas naturais e pode servir como uma futura base militar nesta região.";
			link.l1 = "Mas Helen tem todo o direito à ilha segundo a lei da Inglaterra!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Talvez você não saiba, mas o falecido Sharp fez uma adição ao testamento. O herdeiro, ou herdeiros, devem carregar o sobrenome dele. E, se não me engano, sua garota tem outro sobrenome. Você disse que era McArthur, certo?";
			link.l1 = "Esse é o sobrenome do padrasto dela, mas Helen tem todo o direito de usar o nome Sharp, pois é filha da falecida Beatrice Sharp, que era filha de Nicolas.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Excelente! Mas quem pode confirmar isso sob juramento? Os pais adotivos da Helen conheciam a Beatrice Sharp?";
			link.l1 = "Pelo que entendi, não eram. O senhor McArthur considerava ela filha da Gladys, e a Gladys só conhecia o pai da garota.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Que pena. Veja, não encontrei nenhuma menção nos arquivos de que Beatrice Sharp tenha tido filhos. Existe a possibilidade de que não haja nenhum registro oficial do nascimento da criança. Qualquer um pode se dizer neto de Sharp e reivindicar o direito de usar seu sobrenome.";
			link.l1 = "Mas só a Helen tem o mapa completo!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Esta é a carta na manga dela, e talvez fosse suficiente se as autoridades locais não tivessem seus próprios planos para Isla Tesoro. Um documento escrito de próprio punho por Beatrice, com sua assinatura, está nos arquivos. Precisamos encontrar algum documento escrito por ela que comprove o nascimento da filha—da filha que foi entregue àquela Gladys... é, qual era o sobrenome dela?";
			link.l1 = "Chandler. Gladys Chandler de Belize.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Exatamente. Você tem a chance de encontrar algo assim?";
			link.l1 = "Duvido muito. Já se passaram muitos anos. Segundo a lenda, o próprio Capitão Butcher pode ser o pai da Helen. Talvez o antigo carrasco de St. John's possa nos contar algo sobre isso. Ele foi o último a ver o pai dela com vida.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Hm. Ele realmente era um homem divertido. Se não me engano, seu nome era Raymond Baker. Tive a sorte de conversar com ele uma vez. É um homem inteligente e bem instruído. Bem, tente descobrir algo em Antígua e eu vou continuar minhas buscas nos arquivos, talvez encontre algo útil.";
			link.l1 = "Certo. Funciona pra mim.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Me dê o mapa do Sharp e ande logo, fale com o Baker, talvez consiga encontrar alguns documentos com a ajuda dele. Quem sabe até consiga uma prova do nascimento dela.";
			link.l1 = "Ah, quem me dera. Tudo bem, até mais, senhor Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "É mesmo? Vamos dar uma olhada nessa prova.";
			link.l1 = "Esta é uma carta particular escrita por Beatrice Sharp para o irmão dela. Aqui diz que ela teve uma filha e que o pai, na verdade, era Lawrence Beltrope. A menina foi entregue a uma jovem viúva chamada Gladys Chandler. Lawrence Beltrope também é conhecido como Capitão Butcher. Aqui, fique com a carta...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Gladys está pronta para confirmar isso sob juramento. Ela também está disposta a afirmar que o pai se apresentou como Capitão Butcher.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Espere um pouco! O Capitão Butcher, o pirata cruel e assassino de súditos ingleses, foi enforcado no forte de St. John's há vinte anos. E Lawrence Beltrope, grande amigo de Richard Doyle, morreu tragicamente há pouco tempo. E, acima de tudo, Doyle queria torná-lo o novo governador de Sharptown!";
				link.l1 = "Ha! Claro, ninguém sabe disso... Eu tenho um depoimento escrito de Raymond Baker, o antigo carrasco de St. John's, dizendo que foi forçado, sob ameaça de morte certa, a fingir a execução do Açougueiro! Aqui, veja você mesmo...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Espere um pouco! O Capitão Butcher, o famoso pirata e assassino de súditos ingleses, foi enforcado no forte de St. John's há vinte anos. E Lawrence Beltrope está vivo e mora em uma das melhores mansões de Port Royal. Além disso, Doyle quer torná-lo o novo governador de Sharptown!";
				link.l1 = "Ha! Claro, ninguém sabe disso... Eu tenho um depoimento escrito de Raymond Baker, o antigo carrasco de St. John's, dizendo que foi forçado, sob ameaça de morte certa, a fingir a execução do Butcher! Aqui, dê uma olhada...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Hm. Muito bem...";
			link.l1 = "Não é engenhoso? O Capitão Butcher conseguiu sobreviver e voltou para a Inglaterra. Ele retomou o nome de Lawrence Beltrope e retornou para cá sem ser notado.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "Mas isso... Isso muda tudo! Publicar a carta da Beatrice vai mostrar que, esse tempo todo, o governador militar estava escondendo o pirata fugitivo Butcher, que deveria ter sido preso na hora e levado a julgamento pelos crimes que cometeu!\nE o depoimento do Baker vai acabar de vez com qualquer argumento contrário! Isso é genial! Com uma carta dessas na manga, vamos derrotar o Doyle de forma limpa e justa!";
			link.l1 = "Fico feliz. Estou contando com você nessa situação. E me diga, como Lawrence Beltrope morreu?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Essa história é de arrepiar, senhor. Encontraram-no no próprio quarto, com o rosto todo retorcido. É difícil imaginar o que poderia ter assustado tanto um homem tão destemido. Dizem que ele estava coberto de geada. O corpo cheio de feridas horríveis, rasgadas, mas nem uma gota de sangue no chão! Só imagine! Nem uma gota!";
			link.l1 = "Sim, isso parece mesmo um pesadelo. Parece que ele foi assassinado... Mas quem poderia ter feito isso?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Não se sabe. Está tudo muito confuso... O médico da guarnição disse que os ferimentos dele não eram fatais. Beltrope morreu de medo, de dor, ou de outra coisa. De qualquer forma, é uma morte misteriosa.";
			link.l1 = "Entendo... E quando o julgamento vai começar?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Tudo depende do senhor. Assim que receber a segunda parte do meu pagamento – 450 doblões – entregarei toda a documentação ao tribunal. Helen terá seus direitos reconhecidos uma semana depois disso.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Muito bem. Aqui estão seus dobrões.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Sim, claro. Vou trazer a quantia que você precisa.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Senhor, você me surpreendeu! Você fez tanto, a ilha quase estava em nossas mãos, mas agora tudo acabou por causa do seu atraso com o meu pagamento! O testamento perdeu a validade e Isla Tesoro agora pertence à coroa inglesa. Vai se tornar uma base militar.";
				link.l1 ="Mas que droga! Parece que todo o meu esforço foi em vão...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Trouxe a segunda parte do meu pagamento, senhor?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Sim, claro. Aqui estão seus dobrões.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Perdoe-me pela minha memória fraca, deixei-os em um baú no meu navio. Vou trazê-los imediatamente.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "Mas isso... isso muda tudo! Publicar a carta da Beatrice significa que Lawrence Beltrope deve ser preso imediatamente e levado a julgamento por seus crimes passados!\nE o depoimento do Baker vai acabar de vez com qualquer argumento contrário! Isso é excelente! Com uma carta dessas na manga, vamos derrotar Doyle de forma justa e limpa!";
			link.l1 = "Estou muito feliz. Quando será o julgamento?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excelente, senhor. Foi um prazer fazer negócios com você. Agora, aqui está o combinado. Volte aqui amanhã. Isso mesmo, você ouviu direito – amanhã! Afinal, sou o melhor advogado do arquipélago e tenho bons contatos.  Traga sua cliente, o julgamento não acontecerá sem ela. Não se atrase e não saia da cidade. E, se puder, traga a última parte do pagamento com você. Estou absolutamente certo da nossa vitória.";
			link.l1 = "Ótimo. Estaremos no seu escritório amanhã, senhor Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur? Não, é Sharp! Bem, venha comigo agora!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Permita-me parabenizá-lo, senhor, e sua protegida. Agora ela é a legítima governante de Isla Tesoro. Isso merece um brinde com champanhe!";
			link.l1 = "Sem dúvida, senhor Loxley. Seu discurso foi excelente. Achei que o coronel Doyle fosse ter um ataque do coração quando você contou ao tribunal que Lawrence Beltrop é o Capitão Butcher.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Sim, o senhor Doyle vai ter que dar adeus ao sonho de uma base militar em Isla Tesoro. E o que ele pode fazer? A lei é a lei e vale para todos, até mesmo para o respeitado coronel.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Todos os documentos estão em ordem e confirmam o direito da Helen à ilha?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "Ouvi dizer que o juiz ordenou a prisão de Lawrence Beltrop. Imagino que ele vai ser enforcado?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Certamente, senhor. Conferi cada vírgula neles. Pode ter certeza de que estão corretas.";
			link.l1 = "Muito bem...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Well, my job is done. The case was tricky, but we have won it together. Now, Sir, you only have to pay me the final part of my fee. No pressure, I realise that you must be busy. But I trust you will find time to bring me the remaining 450 doubloons within a week.\nBesides, a client like you can always count on substantial discounts. I can be of great help to you; I have connections in every capital of the archipelago, even in the hostile ones, so any legal problem you encounter can be settled.";
			link.l1 = "Excelente. Agora já sei a quem perguntar.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "Eu garanto um desfecho favorável até nas situações mais difíceis.";
			link.l1 = "Legal. Preciso ir agora, Helen e eu temos muito o que fazer.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Adeus, senhor.";
			link.l1 = "Adeus, senhor Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Acho que sim, ele é o Capitão Butcher, um pirata e bandido. Mas ele não está em Port Royal agora. Teve sorte de escapar, se embrenhando no interior da ilha. Mas a caçada já começou e ele vai ser pego, com certeza.";
			link.l1 = "Entendo... Os documentos estão em ordem?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excelente! Foi um prazer fazer negócios com você, senhor! Agora pode contar com minha ajuda em qualquer assunto e ainda receber um desconto. Problemas com a lei, uma recompensa pela sua cabeça... Fique à vontade. Sempre vou ficar feliz em vê-lo.";
			link.l1 = "Seria melhor se eu evitasse confusão de vez, mas... as coisas acontecem. Obrigado e até logo, senhor Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "O que quer dizer, senhor? Vai quebrar os termos do nosso acordo?";
			link.l1 = "Exatamente. Eu fiz quase tudo sozinho. Você nem imagina o que tive que fazer para conseguir as provas. E você só pegou os papéis e foi ao tribunal. Novecentos dobrões é mais do que suficiente, tenho certeza disso.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Você fala como um pirata, senhor! Pois bem, não vou à falência perdendo quatrocentos e cinquenta doblões, mas você também não vai ficar rico. Na verdade, você acabou de perder muito mais! E pode perder ainda mais no futuro, quem sabe... Saia da minha casa agora mesmo e nunca mais apareça aqui!";
			link.l1 = "E eu vou fazer isso. Adeus, senhor Loxley.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Não quero falar com você. Cai fora ou vou chamar os guardas!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Senhor, teríamos vencido seu caso se tivesse me procurado antes. O testamento perdeu a validade. Sinto muito.";
			link.l1 = "Ah, sinto muito mesmo! Bem, adeus, senhor Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", senhor. Que bom vê-lo. Precisa dos meus serviços?";
			link.l1 = "Sim. É por isso que estou aqui.";
			link.l1.go = "loxly_1";
			link.l2 = "Não, felizmente não preciso deles no momento. Só queria te cumprimentar.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Estou pronto para te ouvir. Que tipo de ajuda você precisa?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "Estou com problemas com as autoridades inglesas.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "Estou com problemas com as autoridades francesas.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "Estou com problemas com as autoridades espanholas.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Estou com problemas com as autoridades holandesas.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Briguei com os contrabandistas.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Me desculpe, mudei de ideia...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Já estou cuidando do seu assunto. Vai dar tudo certo, pode confiar.";
			Link.l1 = "Obrigado. Vou estar esperando.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iLoxlyPseudoGlobal = CalculateRelationSum(i, true);
			int iRate = abs(ChangeCharacterNationReputation(pchar, i, 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = ""+sTemp+" com "+XI_ConvertString(Nations[i].Name+"Abl")+". Vai te custar "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(pchar.money) >= iLoxlyPseudoGlobal)
			{
				link.l1 = "Muito bem, senhor Loxley, eu concordo. Aqui está o seu dinheiro, e tente resolver tudo o quanto antes.";
				link.l1.go = "relation";
			}
			link.l2 = "Eu não tenho a quantia que você está pedindo agora. Volto mais tarde!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			i = sti(npchar.quest.relation);
			dialog.text = "Foi um prazer fazer negócios com o senhor. Pode respirar aliviado novamente, seu problema vai desaparecer nas próximas duas semanas. Por favor, evite qualquer confronto com "+XI_ConvertString(Nations[i].Name+"Abl")+", enquanto estou no meio de negociações.";
			link.l1 = "Certo, vou levar seu aviso em consideração. Obrigado e até logo!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			iLoxlyPseudoGlobal = CalculateRelationContraSum(true);
			dialog.Text = "E por que você fez isso? Os contrabandistas são gente boa, honestos à sua maneira. Todos precisamos viver e comer... Tudo bem, não é nada grave e vai te custar só "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(Pchar.money) >= iLoxlyPseudoGlobal)
			{
				Link.l1 = "Muito bem, senhor Loxley, eu concordo. Aqui está o seu dinheiro, e tente resolver tudo o quanto antes.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Eu não tenho a quantia que você está pedindo agora. Volto mais tarde!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Excelente, vou resolver seu problema. Logo eles vão querer fazer negócios com você de novo.";
			Link.l1 = "Obrigado!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
