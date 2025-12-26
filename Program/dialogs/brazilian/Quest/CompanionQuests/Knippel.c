void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Ah, que calor hoje. Dá vontade de amarrar uma corrente no tornozelo e pular no mar, só pra se livrar desse abafamento!";
			link.l1 = "Ha-ha, Charlie!.. Isso é que são medidas radicais, se quer saber. Mas eu não recusaria molhar a garganta – hoje está quente demais mesmo. Você topa?";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Tomar um ou dois drinques com você, Capitão? Sempre!";
			link.l1 = "É isso que eu gosto de ouvir. Vamos!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_1");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Ei, marinheiro, você parece que já viu de tudo! Que tal tomar um gole e trocar umas histórias? É por minha conta!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Ah, não, obrigado, camarada. Vim aqui com meu Capitão. Procure outra pessoa.";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ha, um trapo como você tem opiniões tão altas, só bebe com capitães?";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Opiniões elevadas?! Eu servi por décadas na Marinha Real! E não lutei pelos nobres, mas pelo povo comum, como eu e você, para garantir lei e ordem em todo lugar!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Fala bonito, mas só bebe com capitães e nobres! Pelo visto, a Marinha te ensinou mesmo foi a dar brilho nos canhões, hein!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Vou enfiar uma bala de corrente na sua goela, moleque!";
			link.l1 = "Charlie, não precisa surtar assim, não vale a pena.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Deixe comigo, Capitão. A honra da Marinha está em jogo, preciso defendê-la eu mesmo, não vou me esconder atrás de ninguém...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_1");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Obrigado por esperar, Capitão. Espero não ter demorado demais.";
			link.l1 = "Não se preocupe com isso. Você não se machucou? Aquele canalha era bem habilidoso.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Não se preocupe, Capitão. O importante é que ele teve o que merecia. Peguei uma espécie de chave no corpo dele...";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "Peguei uma espécie de chave no corpo dele... Fico pensando para que será?";
			link.l1 = "Elementar, Charlie... Para uma porta ou um baú, ha-ha. Devíamos conversar com o estalajadeiro sobre esse canalha, pode ser útil.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Inacreditável...";
			link.l1 = "Você está pensando o mesmo que eu, Charlie?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Eu não sei quanto a você, senhor, mas me surpreende ver tanto dinheiro aqui – ele parecia um homem comum, não um comerciante ou nobre.";
			link.l1 = "Não é grande coisa, de verdade, mas você tem razão. O que me surpreende é essa carta queimada estranha.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "É, isso não foi nada esperto da parte dele – é como atirar bala encadeada num casco reforçado. Ele devia ter destruído a carta por completo.";
			link.l1 = "Verdade. Mas isso não nos ajuda – não sabemos quem ele era, nem com quem se correspondia. Vamos, Charlie, não temos mais nada pra fazer aqui.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2_1");
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "Tanto faz para a sua tão exaltada Marinha Real, pfft!";
			link.l1 = "Charlie era um homem bom, decente. E ele era artilheiro, não fuzileiro.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Um canhoneiro?! Então, é exatamente como eu disse, ha-ha-ha! E não me olhe assim – você devia saber quem estava colocando na sua tripulação.";
			link.l1 = "Você devia saber com quem estava se metendo.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Você ainda está vivo só porque venceu de forma justa, então feche essa boca podre e suma daqui.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Bem, achei que teria que lutar com você em seguida. É bom saber que honra ainda significa algo para você.";
			link.l1 = "Não foram só palavras vazias para o Charlie também. Mas quanto a você, eu tenho minhas dúvidas. De qualquer forma, isso já não importa.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_2");
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "E com quem eu fui mexer, um franguinho mimado?! Já viu esse seu bigodinho ralo?..";
			link.l1 = "Você realmente sabe como provocar... Vai ser ainda mais gostoso descontar minha raiva em você.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_3");
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Espere, Capitão. Vejo que é um homem digno e nobre, pode me ajudar com uma coisa? É uma questão de honra.";
			link.l1 = "Talvez eu possa, mas qual é o problema? E por que veio falar comigo? Tem muita gente importante por aqui. Aliás, com quem tenho a honra de falar?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. Vejo que você não é um desses herdeiros mimados de família tradicional, mas sim um homem confiável, de mão firme.";
			link.l1 = "Ah, o senhor devia ter me visto quando cheguei ao Caribe pela primeira vez. Mas diga lá, em que posso ajudar?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "O senhor poderia... duelar por mim? Um encrenqueiro local, Ralph Faggle, insultou minha esposa. E ainda a importunou, em público. Bem na minha frente. Dá pra acreditar nisso?";
			link.l1 = "Não há muita honra em desafiar para um duelo e depois se esconder atrás de outra pessoa. Principalmente quando não está em jogo só a sua honra, mas a de uma mulher — sua esposa, nada menos. Não acha, Adams? Por que não luta por sua mulher você mesmo?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "E você está certo, absolutamente certo. Mas recentemente sofri com uma febre forte, e mal consigo ficar de pé\nConfesso que não é fácil lhe pedir algo assim. Se ele tivesse me insultado, eu teria aguentado. Mas não quando a honra da minha esposa está em jogo! Não sou covarde, senhor. Já servi na Marinha Real e naveguei no mesmo navio que o próprio Robert Blake!";
			link.l1 = "Eu...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Vamos te ajudar.";
			link.l1 = "Charlie?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "Ele é um homem de valor, Capitão. E que eu seja condenado para sempre por uma chuva de balas de canhão se isso não for verdade! Grandes pessoas serviram com o Almirante Blake. Lutaram juntos para que ninguém oprimisse o povo comum\nE graças a ele, a Jamaica foi libertada da tirania dos espanhóis!";
			link.l1 = "Mesmo que seja esse o caso, não vou permitir que meus homens me interrompam ou tomem decisões por mim. Está claro?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Eu entendo, de verdade. Mas eu nem tive a chance de responder. Tente não ser tão apressado e me interromper da próxima vez, tudo bem?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Vou te dizer uma coisa, Capitão – se você não ajudar esse homem, o velho Charlie larga tudo e vai duelar por ele sozinho, que eu seja amaldiçoado aqui mesmo!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Calma aí, eu não disse que me recuso a ajudar. Certo, Sr. Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Para ser sincero, Charlie, você está me fazendo parecer um covarde. E eu nunca fui um. Você devia saber disso.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Ah, desculpe, Capitão, me empolguei.";
			link.l1 = "Está bem. Mas controle-se, certo?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Eu vou duelar por você, Sr. Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Obrigado, senhor! Deus te abençoe!";
			link.l1 = "E que o Senhor Protetor também seja abençoado, não é, Sr. Adams? Não se preocupe, Charles de Maure nunca abandona um homem honesto em apuros.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Agradecemos muito, Sr. de Maure, senhor! Gostaria de vir jantar comigo e com a Jane?";
			link.l1 = "Bem, eu...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "Eu insisto!";
			link.l1 = "Bem, só se você fizer questão. Obrigado, Peter. Mostre o caminho.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Claro que é verdade, senhor! Gostaria de vir com a Jane e descansar depois da viagem?";
			link.l1 = "Obrigado, mas será que é certo aproveitar da sua hospitalidade?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "Oh, pelo contrário, Capitão, ficaríamos ofendidos se o senhor não viesse.";
			link.l1 = "Como eu poderia recusar naquela hora? Depois de você, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_3");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "Somos nós! Por favor, entre.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Obrigado. Posso falar com a Jane? Pergunte a ela como aconteceu - preciso de todos os detalhes.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Me desculpe mesmo, mas pensando melhor, vou ter que recusar. Tenho um duelo para me preparar. Aliás, onde e quando vai ser?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Claro, senhor. Nós dois vamos conversar com o senhor e responder a todas as suas perguntas. Por favor, me acompanhe.";
			link.l1 = "Obrigado, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Que pena! Mas você está certo, é claro que deve se preparar bem. Duas horas. Bem ali fora dos portões da cidade.";
			link.l1 = "Entendido, obrigado. Vou até aí assim que tudo acabar. Até lá!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_4");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Bem-vindo! Ora, você não me disse que traria convidados – eu teria me preparado melhor.";
			link.l1 = "Obrigado, senhora, não vamos demorar. Charles de Maure, ao seu dispor. Concordei em ouvir sua história junto com seu marido. Conte-me como tudo aconteceu.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Ah, foi horrível! O Ralph estava completamente bêbado. Começou a me importunar na frente dos vizinhos, até mesmo na frente do Peter, dizendo coisas obscenas...";
			link.l1 = "O que exatamente ele te disse?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Estou envergonhado demais para falar sobre isso. Depois ele ficou sóbrio, e...";
			link.l1 = "Pediu desculpas e tentou cancelar o duelo, talvez?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Nem uma vez.";
			link.l1 = "Sinto muito por você. Gostaria de saber mais uma coisa, se permitir, senhora.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "E o que seria isso, senhor?";
			link.l1 = "Que circunstâncias da vida e provações forçaram você e seu marido a viverem aqui? Em qualquer cidade inglesa, pelos méritos do seu marido, você já teria colocado o Ralph no devido lugar.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Com todo o respeito, senhor, mas como ousa?! Se não fosse meu capitão, eu pegava uma bala de corrente e te dava uma boa surra!\nNão só desconfia de um homem tão digno quanto o Sr. Adams, como ainda zomba de uma dama em apuros...";
			link.l1 = "Você me ouviu zombar de uma dama? Não? Então não me calunie. Nosso pessoal poderia ter ajudado eles, foi por isso que perguntei.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Calma, Charlie! Como você pôde... Eu só queria saber mais sobre as dificuldades da Jane e do Peter e me solidarizar com eles. Nas colônias inglesas, com certeza eles já teriam recebido ajuda.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "A vida pode tomar muitos rumos... Um naufrágio. Ou a calúnia de alguém, que às vezes pode forçar até as pessoas mais honestas a se esconderem em desgraça\nSe você está tão desconfiado e suspeita de tudo – pode falar com os vizinhos. Tenho certeza de que vão confirmar cada palavra. Mas o velho Charlie jamais se rebaixaria a falar das desgraças dos outros pelas costas!";
			link.l1 = "Você não me ouviu? Eu disse que ia ajudar essas pessoas.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "A vida pode tomar muitos rumos... Um naufrágio. Ou a calúnia de alguém, que às vezes pode forçar até pessoas honestas a se esconderem na vergonha\nSe você está tão desconfiado e suspeita de tudo – pode conversar com os vizinhos. Tenho certeza de que vão confirmar cada palavra. Mas o velho Charlie jamais se rebaixaria a falar das desgraças dos outros pelas costas!";
			link.l1 = "Você não me ouviu? Eu disse que ajudaria essas pessoas.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Muito obrigado, de todo o coração. Vamos lembrar de você em nossas orações.";
			link.l1 = "Que bom. Aliás, sobre o nosso assunto. Onde e quando você marcou o duelo, Sr. Adams?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "Fora dos portões da cidade, senhor. Em duas horas.";
			link.l1 = "Eu vou conseguir. Espere por boas notícias minhas. E nem pense em acender uma vela pela minha alma antes da hora!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Tem alguma coisa te incomodando, Capitão? Você está com um olhar bem pensativo.";
			link.l1 = "Sabe, é. Tem algo na história do Adams que não bate, e...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Por quanto tempo isso vai continuar, senhor?! O senhor sempre reage assim quando alguém precisa de ajuda?";
			link.l1 = "Pelo amor de Deus, fale baixo. Você quer gritar isso pra rua toda? Eu já disse que vou ao duelo. Não basta pra você? Agora me escute com atenção.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Tá bom, Capitão. Desculpe pelo meu desabafo – eu me importo com o destino de quem serviu na Marinha Real. Muitos de nós eram gente decente, mereciam um destino melhor do que tiveram.";
			link.l1 = "Eu entendo você, Charlie. Agora lembre-se do que precisa ser feito. Quero que envie alguns dos homens para os portões da cidade. Quando a hora do duelo se aproximar, deixe que se reúnam discretamente e fiquem prontos para o meu sinal.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Você pretende transformar um duelo honesto em assassinato?";
			link.l1 = "Eu suspeito que isso não vai ser totalmente honesto. Só vou sinalizar se for mesmo necessário. Se tudo estiver realmente limpo, vou ficar feliz em estar errado. Agora você entende? Lembra do que aconteceu há um mês?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Entendido, senhor. Sinceramente, não estou muito satisfeito com isso, mas vou fazer o que for preciso. Não se preocupe.";
			link.l1 = "Era isso que eu queria ouvir.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_5");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "Então, de Maure. Você chegou cedo. E ainda estamos na cidade. Mas isso não importa. Pena que não trouxe aquele velho tolo com você. Mas não se preocupe, vamos chegar até ele uma hora ou outra.";
			link.l1 = "À disposição, sempre. Mercenários, é isso? Com quem foi que me indispose?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "É isso mesmo, ninguém. Estamos atrás daquele velho rabugento, o Charlie, e é mais fácil encontrá-lo por você, já que soubemos que agora ele está no seu navio. Aqui não é a selva, então vamos ter que agir rápido pra não chamar atenção. Mas aqui, pelo menos, você não vai escapar.";
			link.l1 = "Acho que esse duelo todo era uma armadilha, não é?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Um pouco tarde pra perceber isso, amigo. A gente teria lutado de qualquer jeito – sou Ralph Faggle, ao seu dispor.";
			link.l1 = "Na verdade, eu já desconfiava disso, então resolvi conversar com os vizinhos. Aliás, o Adams também está envolvido nisso? E a Jane? Será que ela poderia estar...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "A curiosidade matou o gato, não te contaram? Mandaram você aparecer para o duelo, não para ficar bisbilhotando. Ainda pode ter uma chance de sair vivo dessa confusão\nClaro. Provocar o velho marinheiro e obrigar o oficial dele a duelar – foi um plano brilhante que bolamos com o Peter, eu acho. E a Jane também fez a parte dela direitinho.";
			link.l1 = "Me diga, quem queria se livrar do Charlie?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ha, como se eu fosse te contar? Se defenda.";
			link.l1 = "Pena. Então vou perguntar ao Peter mais tarde.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Ah, vejo que levou minha história a sério e já puniu o Ralph, Capitão.";
			link.l1 = "Claro, já que, como você disse, sou um homem digno e honrado. E agora vou ter que te punir por essa armadilha traiçoeira.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Pode tentar, Capitão – imagino que já esteja exausto e ferido.";
			link.l1 = "Então vamos fazer uma pausa. Enquanto isso, me diga, para quem você trabalha?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Desculpe, mas meu patrão não iria gostar disso, mesmo que eu desse um jeito em você depois. Aliás, é exatamente isso que vai acontecer agora.";
			link.l1 = "Droga!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Não acredito que esses... esses canalhas não só nos enganaram, mas também mentiram sobre a Marinha Real! Como ousam! Se não estivessem mortos, eu faria eles engolirem umas balas de corrente por tamanha traição!..";
			link.l1 = "As pessoas mentem sobre todo tipo de coisa, Charlie. Achei que você soubesse disso muito bem. Mas o que você certamente sabe é quem os enviou. Não é a primeira armadilha que armaram pra você ultimamente. Eles tinham uma carta com uma descrição detalhada sua. Quem você irritou tanto assim?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Bem, eu... Talvez a gente encontre outra coisa na casa dos Adams, senhor?";
			link.l1 = "Fugindo da pergunta? Mas você tem razão, eu ia vasculhar tudo de qualquer jeito. Vamos.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Por todos os canhões, quanta riqueza!";
			link.l1 = "Que pena que não tem mais nada aqui. A 'Jane' também não está em lugar nenhum. Você acha que ela ainda está viva?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Eu não sei, senhor, esses canalhas são capazes de qualquer coisa...";
			link.l1 = "É verdade, mas me parece que você sabe mais do que está dizendo. Não é a primeira vez que eles te caçam. E toda vez encontramos uma pilha de dinheiro com eles.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Não tenho certeza, Capitão, mas talvez tenha sido um agiota de St. John's.";
			link.l1 = "Como você se voltou contra ele?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Bem... faz um tempo, eu peguei dinheiro emprestado com ele pra quitar todas as minhas outras dívidas. O Richard prometeu que ia pagar, mas...";
			link.l1 = "Você acha que ele não fez isso?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Eu não teria acreditado nisso antes, mas depois do que ele fez com você e saiu às pressas do Caribe com a Abi... Talvez ele tenha esquecido da dívida. Ou não esqueceu, mas foi embora mesmo assim... O Richard agiu como um verdadeiro canalha, senhor. Eu não ficaria surpreso, mas ainda assim decepcionado, se isso acabar sendo verdade de novo.";
			link.l1 = "Não seja tão categórico antes da hora, Charlie. Então, vai ser St. John's mesmo.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Ah, aqui está você, senhor - parece que todos decidiram chegar cedo. Pelo seu jeito, parece estar bem tranquilo, está mesmo tão confiante nas suas habilidades?";
				link.l1 = "Naturalmente, este está longe de ser o meu primeiro duelo.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "Eu temi que o senhor não viesse. Os outros já estão aqui.";
				link.l1 = "Um verdadeiro cavalheiro só pode se atrasar para a própria morte.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Palavras maravilhosas, senhor! Conheça nosso adversário, Ralph Faggle. E este é nosso segundo, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Encontrar...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Nosso adversário, Ralph Faggle.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "E este é o nosso segundo, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "Então este é o Ralph? Ele não parece um vizinho bêbado qualquer.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "Você nunca sabe quem pode ser seu vizinho, já pensou nisso, Sr. de Maure? Heh-heh-heh.";
			link.l1 = "Então, é uma armadilha... Vejo que até parou de tremer. Cansou de fingir que está doente?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "A única coisa que consigo sentir agora é vontade de rir da sua ingenuidade.";
			link.l1 = "Pois bem, pois bem. Só lamento que o Charlie tenha vindo junto – teria sido mais fácil e silencioso lidar com você sozinho...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Bem, isso é maravilhoso!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Permita-me apresentar...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "Sr. Stokes, nosso imediato.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "E este é o Ralph Faggle.";
			link.l1 = "Então esse é o Ralph? Tenho que admitir, imaginei ele de outro jeito. Mas não importa, já lidei com coisa pior.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hum, fico pensando, será que você é ingênuo, sem entender nada? Ou confiante demais?";
			link.l1 = "E o que é que eu não entendo, Sr. Adams? Vamos lá, me surpreenda.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Geralmente, as pessoas ficam surpresas ou assustadas em situações assim, mas você parece ser de outro tipo. Vai ser ainda mais prazeroso arrancar esse sorriso convencido do seu rosto, Sr. de Maure.";
			link.l1 = "Que ameaças! Não estamos do mesmo lado, Peter?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Não me diga que você espera derrotar todos nós com esse velho aí. Você está em desvantagem, meu caro senhor.";
			link.l1 = "Como eu disse, é VOCÊ que não entende. Charlie resmungou um pouco, mas mesmo assim eu mandei ele trazer os caras aqui, por precaução. Pelo visto, não foi à toa. GALERA, VENHAM AQUI!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "O quê?..";
			link.l1 = "Surpreso e assustado, Sr. Adams? Bom saber.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "É assim que se lida com canalhas mentirosos desses. Ainda não acredito que tiveram a cara de pau de mentir sobre a Marinha Real! Eu estrangularia esses desgraçados com uma bala de corrente!..";
			link.l1 = "Já devia saber que tem gente sem nenhum escrúpulo, Charlie. Eu disse que cuidaria disso, você podia ter ficado no navio. Queria ter certeza de que eu ia ajudar esses 'bons cidadãos'? E quem estava certo de novo, que não era tão simples quanto você pensou?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Você, senhor...";
			link.l1 = "Exato. Mas me diga, por que alguém iria querer te caçar? Não é a primeira vez.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Não sei, Capitão. O velho Charlie é só um canhoneiro simples.";
			link.l1 = "Hum, muito bem, muito bem. Certo, já que nossos pobres duelistas não tinham nada de útil com eles... Não, vamos ver se conseguimos encontrar algo na casa do Adams.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "Então, essa mulher também sumiu... Será que eles estavam se preparando pra fugir da cidade logo depois daquele 'duelo'? E às pressas – tem tanto ouro aqui!";
			link.l1 = "Você está certo, porque ouro não foi a única coisa que eles deixaram para trás. Tem outra carta. Eles estavam com tanta pressa que esqueceram de queimá-la. Olha, você vai gostar do que está escrito.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(lendo) Bem, eu discutiria sobre o 'velho'.";
			link.l1 = "Isso não vem ao caso agora. Já é a segunda vez que mandam mercenários atrás de você, dando dinheiro e informações. E eles querem você, justamente você. Me diga, seu simples artilheiro, quem foi que você conseguiu irritar tanto assim?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "Tenho um palpite, senhor, só um, e realmente não quero que seja verdade.";
			link.l1 = "Então, é bem provável que seja verdade. Fale logo.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "Eu já tive dívidas com várias pessoas em St. John's, e...";
			link.l1 = "... e agora você acha que estão te caçando? Quantos podem pagar mercenários e esse tipo de quantia?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "Está pensando certo, senhor. No fim das contas, quitei quase todas as minhas dívidas pegando dinheiro emprestado com um agiota. Ele pode bancar tudo isso, claro. Mas...";
			link.l1 = "Mas o quê? Vamos pagar sua dívida, e pronto. O que te preocupa?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Veja, Capitão, o Richard me prometeu que pagaria isso por mim.";
			link.l1 = "Você acha que ele não fez isso?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Eu já não sei mais o que pensar, senhor. Durante todo o tempo em que o conheci, ele sempre foi um verdadeiro cavalheiro. Mas depois que ele te deixou e fugiu com a Abigail... já não me surpreenderia. Por isso disse que preferia que não fosse verdade.";
			link.l1 = "As suposições precisam ser verificadas primeiro, depois você pode ficar chateado, Charlie. Vamos, você vai voltar a St. John's.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Capitão!!!";
			link.l1 = "O que foi, Charlie, o que aconteceu?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Aconteceu?! Não me diga que esqueceu do duelo, senhor! O Adams já pode ter sido cortado em pedaços enquanto o senhor fica aí parado!";
			link.l1 = "Certo!.. Vou sair da cidade imediatamente.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Capitão Charles de Maure? É o Charlie Knippel que está com você?";
			link.l1 = "Não, isso...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Não negue, senhor – todo mundo nesta colônia conhece o Charlie.";
			link.l1 = "Então por que perguntar? Como posso ajudar?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Você não pode. Por favor, não resista – Charlie é procurado aqui. Temos que levá-lo sob custódia.";
			link.l1 = "Posso saber de que acusam o meu homem? É por causa de uma dívida? Eu posso pagar por ele. Vamos ao banqueiro agora mesmo, com o senhor junto.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Uma dívida? É a primeira vez que ouço falar disso. Não sei dos detalhes, mas por favor, não complique as coisas – só estou cumprindo ordens.";
			link.l1 = "Ah, que maravilha...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Capitão...";
			link.l1 = "Charlie, se a gente fugir agora, a recompensa pela nossa cabeça vai ser ainda maior. E lutar não é uma opção? Eu vou tentar te tirar dessa, só não faça nenhuma besteira!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Pare de fazer barulho e de ameaçar este homem imediatamente, senhor. Entregue suas armas e me acompanhe agora mesmo!";
			link.l1 = "Eu não ameacei ninguém, houve um engano. Isso é uma questão de negócios, não uma tentativa de assassinato.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Não me parece, não. Você vai ter que responder perante a lei.";
			link.l1 = "E se eu pedir desculpas e for embora?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "Então você quer voltar escondido e terminar o que eu interrompi? Acha que eu sou idiota?";
			link.l1 = "Deve ser, se não quer resolver isso de forma pacífica. Deus sabe que eu não queria que chegasse a esse ponto...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "Você matou ele!..";
			link.l1 = "Considere isso feito por suas próprias mãos, senhor. Você podia ter simplesmente respondido às minhas perguntas em vez de fazer esse escândalo. Juro, mais um grito e eu estouro seus miolos.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Sim, fui eu que matei ele. Ele me obrigou. Mas você não é tão cabeça-oca quanto ele e não vai seguir o exemplo dele, certo?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "O que você quer?!";
			link.l1 = "Há algum tempo, Charlie Knippel pegou dinheiro emprestado com você. O amigo dele prometeu quitar a dívida, mas pelo visto não fez isso. Exijo que pare de mandar mercenários atrás de nós imediatamente. Estou pronto para pagar a dívida do Charlie agora mesmo, se eu tiver condições.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "O que você quer?!";
			link.l1 = "Há algum tempo, Charlie Knippel pegou dinheiro emprestado de você. O amigo dele prometeu quitar a dívida, mas pelo visto não cumpriu. Exijo que pare de mandar mercenários atrás de nós imediatamente. Estou pronto para pagar a dívida do Charlie agora mesmo, se eu tiver condições.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! I would never do that to him; he's a good, honest man. Besides, his debt has long been paid off. Mr. Fleetwood, the captain of the Valkyrie, settled it to the last peso.";
			link.l1 = "Sério? Eu sei quem ele é. Você devia ter dito isso logo. Desculpe pelo incômodo, adeus.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Assim mesmo?! Você me ameaçou! E matou um homem!..";
			link.l1 = "Esqueceu o que eu disse? Mais um grito e você vai junto com ele. Adeus.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Ainda está por aqui e não foi enforcado ainda? Pois bem, um abraço do Sussex, Charlie.";
			link.l1 = "Saudações para você, seja lá quem for.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Ah, Charles de Maure. Que bom que veio ver o velho Charlie. Já estávamos esperando por isso.";
			link.l1 = "Quem somos nós?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Não importa. Você nos fez perder tempo e dinheiro, Sr. de Maure. Acho que ninguém vai se importar se eu resolver logo aqui com você e o Charlie.";
			link.l1 = "Bem, já que estamos ambos mortos mesmo, poderia nos dizer, por pura bondade, quem foi que irritamos tanto? Prometemos não fazer de novo. E quem é Sussex?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Não posso. O dever chama e, diferente de você, sou um homem de ação, não de palavras.";
			link.l1 = "Pelo amor de Deus, será que alguém vai me explicar o que está acontecendo?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Killer_5");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Bem, eu que me dane, Capitão, que carnificina você fez aqui!";
			link.l1 = "Tem alguma objeção? Prefere a forca? Ou quem sabe apodrecer aqui para sempre?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "Não, senhor. Obrigado por me resgatar. Para ser sincero, fiquei surpreso que veio atrás de mim, considerando o quão fácil você deixou que me levassem. E também me surpreendi com a facilidade com que lidou com o guarda – ele era um Sea Fox. Um fuzileiro.";
			link.l1 = "Eu disse que ia te tirar daqui, não devia ter duvidado. Agora sai dessa cela antes que a guarnição inteira apareça.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Sim, senhor, Capitão.";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "Merda, senhor, mal posso acreditar nisso...";
			link.l1 = "Aliás, me diga, do que te acusaram? E quem é Sussex?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Não sei, senhor. Não faço ideia de quem eles estavam falando...";
			link.l1 = "Certo, vamos descobrir isso depois. Agora precisamos sair daqui.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Quais são seus próximos passos, senhor? Enfrentar aquele sanguessuga em plena luz do dia é arriscado demais.";
			link.l1 = "Você acabou de me dar uma ideia. Por que esperar até o dia para dar uma lição nele se podemos fazer isso agora, sob a proteção da noite?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Caramba, essa é uma ideia brilhante, Capitão!";
			link.l1 = "Exato. Me diga, Charlie, você morou aqui por um tempo. Sabe onde mora o agiota?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Eu sabia, senhor, mas da última vez que estive aqui, ele estava vendendo a casa. Não faço ideia de onde fica a nova.";
			link.l1 = "Bem, isso é um problema...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Tenho certeza de que você vai dar um jeito, Capitão, afinal, derrotou o temido Lucas Rodenburg!";
			link.l2 = "Certo, eu cuido disso. Mas, se você soubesse onde fica a casa do agiota, seria melhor!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "Fiz isso sim. Mas a manhã é mais sábia que a noite, Charlie. Vamos descansar da viagem e ir durante o dia – afinal, não viemos aqui para matar o homem.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Tem certeza disso, senhor? Vamos perder o elemento surpresa.";
			link.l1 = "Tenho certeza e estou cansado. Além disso, só quero conversar. Assustar ele um pouco, se precisar.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "O que eu não sei - eu não sei, desculpe, senhor.";
			link.l1 = "Ah, deixa pra lá, vamos procurá-lo.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Está pensando o mesmo que eu, senhor?";
			link.l1 = "Receio que sim, Charlie. Não há outro capitão famoso com esse nome no Caribe. E Richard realmente foi para Londres. Então, é improvável que seja coincidência.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Horrível... Apesar de ter dito muitas coisas duras sobre ele, nunca desejei algo assim! E a pobre Abi!.. Ela estava esperando um filho. Tomara que esteja viva...";
			link.l1 = "De fato, não desejaria isso a ninguém. Tomara que a Abi esteja bem. Alguma ideia de quem poderia ter feito isso com o Dick? Ele já mencionou algum inimigo poderoso?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Você só pode estar brincando, Capitão. Não sei como é na Europa, mas aqui todo holandês queria o Richard morto.";
			link.l1 = "Verdade. Talvez alguém daqui tenha gastado uma fortuna e mandado assassinos atrás dele para o Velho Mundo. Será que não é esse agiota mesquinho que está por trás dos ataques contra você, mas sim algum inimigo misterioso do Richard?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Não sei, senhor. Tudo é possível neste momento. Mas isso complicaria as coisas para todos nós...";
			link.l1 = "Sim, você está certo, eu também não gosto dessa possibilidade.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "O quê, quem... O QUÊ?! O que está acontecendo?.. Quem é você?!..";
			link.l1 = "Ah, qual é. Se eu quisesse te matar, faria isso enquanto você dorme. Então vamos evitar complicar ou encurtar nossas vidas. Faça que sim com a cabeça se entendeu.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Mm-hmm...";
			link.l1 = "Muito bem. Calma – não estou aqui para roubar, sequestrar ou te machucar.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Então... por que você está aqui? Por que não pôde vir de manhã?";
			link.l1 = "Porque algum sujeito rico e influente está caçando meu amigo. Temos motivos para acreditar que é você, então provavelmente não é seguro para ele andar por essas ruas em plena luz do dia.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "Mas eu realmente não entendo do que o senhor está falando...";
			link.l1 = "Charlie Knippel. Todo mundo na cidade conhece ele. Pensa bem. Ele te deve dinheiro.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Nosso velho Charlie?? Isso é verdade, mas a dívida dele foi paga há muito tempo, embora não por ele mesmo.";
			link.l1 = "E quem era esse benfeitor?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "O capitão dele, lorde Richard Fleetwood. Se não acredita em mim, posso mostrar meus registros.";
			link.l1 = "Fleetwood, você disse? Então eu acredito em você. Então, não foi você quem mandou mercenários atrás do Charlie?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Claro que não, por que eu faria isso?? E me diga, que sentido isso teria?";
			link.l1 = "De fato. Bem, desculpe pela visita tardia. Boa noite.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "O que foi, Charlie, queria se esconder com seu antigo protetor hoje à noite? Ele não está lá. Mas logo você vai encontrá-lo. Saudações de Sussex.";
			link.l1 = "Isso a gente já sabia. E quem é Sussex? E quem é você?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "Isso não é da sua conta, Sr. de Maure. Pena que você se envolveu nessa confusão mais do que gostaríamos. Você é um incômodo.";
			link.l1 = "Um incômodo pra quem? Por favor, não me diga que dormi com a esposa de algum inglês muito influente e muito irritado.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Muito engraçado. Achou tempo pra fazer piada. Pelo visto, o que dizem sobre você é verdade\nO que queremos? A cabeça do Charlie já bastaria. Mas, considerando o quanto você nos atrapalhou, desta vez é com você também – vive enfiando o nariz onde não é chamado.";
			link.l1 = "Suponho que estamos presos?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Prender? Não, meu caro, acabou o tempo das meias-medidas. Isto é uma execução, Capitão de Maure.";
			link.l1 = "Concordo. A única questão é: de quem.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Eu não achei que as Raposas do Mar estariam envolvidas...";
			link.l1 = "Bem, sempre tem uma primeira vez pra tudo. Me diga, Charlie, quem é Sussex?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Eu...";
			link.l1 = "Você não percebe até onde isso chegou? E parece que estamos no mesmo barco, Charlie. Então eu tenho o direito de saber os detalhes.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Claro, Capitão. Mas não aqui, certo? Vamos sair da ilha e conversar no navio.";
			link.l1 = "Você tem razão. Certo, vamos depressa.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Chamou, Capitão?";
			link.l1 = "Sim, Charlie. Precisamos conversar. Acho que você já imagina sobre o que é.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Sim, senhor...";
			link.l1 = "Ótimo. Então me diga por que seus compatriotas, até mesmo as forças de elite, estão te caçando se você não é nenhum criminoso ou algo assim.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Eu realmente não sei, senhor...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Isto não é brincadeira, Charlie. Quem está te caçando consegue dar ordens até para as raposas do mar. Provavelmente também está por trás do assassinato do Richard. Então, se você tem alguma ideia, fala agora. Que tipo de recado é esse de Sussex, quem é essa pessoa?";
			}
			else
			{
				link.l1 = "Pare de desviar o olhar, Charlie. Eu vejo que você sabe de algo. Como seu capitão, eu ordeno que me conte tudo. Quem é Sussex?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "Certo, Capitão. Sussex não é uma pessoa. É... um navio.";
			link.l1 = "Saudações de um navio? Isso não faz sentido.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Deixe-me explicar. Posso me sentar, senhor? A história é longa e nada agradável.";
			link.l1 = "Claro, Charlie. Pode falar.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Ei, Charlie, eu vim a mando do Capitão Fleetwood. Ele quer falar com você.";
			link.l1 = "Obrigado, camarada. Aconteceu alguma coisa? Normalmente, ele manda tudo por você na hora.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Não sei. Ele disse que quer conversar sobre isso diretamente com você. É assunto seu, resolvam entre vocês.";
			link.l1 = "Ah, estou com um mau pressentimento sobre isso...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Kurier_3");
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "Boa noite, senhor!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Boa noite. Deixe-me passar.";
			link.l1 = "Claro, prossiga, peço desculpas, senhor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Cortny_3");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Ah, é você, Charlie. Entre, entre. Feche a porta atrás de você.";
			link.l1 = "Boa noite, Capitão. O que está acontecendo? E quem era aquele homem? Um pavão pomposo...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Isso, não posso dizer. E também não posso deixar que ninguém escute nossa conversa. Não conte isso a ninguém, entendeu?";
			link.l1 = "Sim, senhor. Aconteceu alguma coisa? Você parece mais preocupado do que o normal, isso não é do seu feitio.";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Parece que sim para você. Você também não está com a melhor aparência – afinal, já é noite. Mas receio que seu descanso acabou por hoje, meu amigo – temos uma missão urgente e confidencial.";
			link.l1 = "E o que isso vai envolver, Capitão?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Eliminar um traidor. Do nosso próprio meio. Em breve, um navio diplomático vindo do Velho Mundo vai aparecer na costa da Dominica – a fragata 'Sussex'. Oficialmente, eles vêm negociar um bom acordo com os holandeses. Mas, na verdade...";
			link.l1 = "... eles vão passar informações para os nossos inimigos, senhor?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "   Pior ainda. Vão desertar completamente para o lado deles. E mesmo que estejam exaustos depois de cruzar o Atlântico, no fim das contas, é uma bela fragata que com certeza vai tentar fugir se atacarmos com um navio pesado.\nEntão precisamos agir rápido e com decisão. Só podemos contar com a 'Valkyrie' – ela é a única capaz de cumprir essa missão.";
			link.l1 = "A velha 'Valkyrie' vai aguentar um navio de guerra?.. ";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ha-ha, Charlie, está duvidando do seu capitão? Além disso, como eu disse, eles vão estar exaustos. Se atacarmos de surpresa, todas as vantagens serão nossas.";
			link.l1 = "Eu jamais faria isso! Mas espero que saiba o que está fazendo, senhor...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "Tenho certeza disso. E mais uma coisa. Esse traidor ocupa um cargo importante no próprio Parlamento, entendeu? Ele pode ter olhos e ouvidos em toda parte – não só em casa, mas já aqui, no Caribe. Então não mencione Sussex nem nenhum detalhe da nossa missão na cidade.";
			link.l1 = "Não precisava me dizer, senhor. Pode sempre contar com o velho Charlie.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Eu sei. Só que, desta vez, as apostas são mais altas do que nunca. Junte suas coisas e prepare-se – zarpamos ao amanhecer.";
			link.l1 = "Sim, senhor. Boa noite, senhor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_9");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Eu nunca vi o Richard assim... Ele estava tão preocupado ou até mesmo... com medo?";
			link.l1 = "Mas por quê? Ele nem sequer me contou. Bem, não importa. Ele é um grande capitão, então com certeza vamos dar conta dessa fragata e da tripulação cansada dela.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Knippel_SamSoboi_2");
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "O 'Sussex' está no horizonte, Charlie, prepare-se.";
			link.l1 = "Sempre pronto, Capitão.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Muito bem. Conto com você e sua bala encadeada. Tente rasgar as velas deles o mais rápido possível, ou melhor ainda, derrubar um mastro. Não faz sentido arriscar tudo numa luta só para afundá-los, então vou tentar abordar o navio\nAlém disso, precisamos garantir que o traidor esteja morto – se afundarmos o navio, ainda teremos que nos aproximar e ter certeza de que ninguém sobreviveu.";
			link.l1 = "E matar tantos compatriotas por causa de um traidor só...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Infelizmente. Também me dói, Charlie. Mas ordens são ordens. Pelo menos não estamos fazendo isso por diversão. Então vamos acabar logo com isso.";
			link.l1 = "Sim, senhor...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_13");
		break;
		
		case "DTSG_Graf_Sheffild_1":
			dialog.text = "Chega! Estou pronto para entregar minha espada e ouvir suas exigências. Mas antes, apresente-se! Quem é você e como ousa nos atacar?! Isso é traição!";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Capitão Richard Fleetwood. E você deve ser o Conde Sheffield? E você está absolutamente certo, isso é traição.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "Você sabe quem eu sou? Droga! Eu sabia que algo assim ia acontecer, ratos por toda parte, então pedi, até implorei por um navio de guerra...";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "Não teria te salvado, só teria adiado o inevitável, porque eu encontraria outro jeito. E sim, quando falo em traição, falo da sua, Conde Sheffield.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Então você não sabe nada sobre mim, senhor! Todo mundo sabe que não existe homem mais leal à Inglaterra do que eu! Você ainda vai se arrepender desse erro, pode apostar.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Não tenho do que me arrepender, já que não sou eu quem está desertando para os holandeses.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "O quê?! Que bobagem é essa que você está dizendo?! Você foi enganado e seguiu uma pista falsa feito um cão louco\nAhem, é verdade, estou indo negociar com a Companhia Holandesa das Índias Ocidentais. Mas é pelo bem da nossa Inglaterra, Capitão. Isso é um erro terrível, mas ainda podemos consertar.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "Receio que isso não depende de mim. E certamente não depende de você. Vocês escolheram o lado errado, senhores. Adeus.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Terminamos aqui. Achei que aquele gordo nunca ia parar de chiar. Ah, esses condes, não é, Charlie?";
			link.l1 = "Eu só fico pensando, senhor, e se o coronel estivesse errado? Ou, Deus me livre, se ele mentiu pra gente só pra se livrar do Conde?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Me escute, meu amigo. E preste muita atenção. Nosso serviço é perigoso e difícil, em todos os sentidos. Qualquer coisa pode acontecer – um erro trágico, uma coincidência absurda, ou uma traição covarde\nServir ao país não é só carregar canhões com balas, Charlie. Para quem manda, é tomar decisões difíceis. E para soldados como nós – é cumprir essas decisões.";
			link.l1 = "Mas e se um dia derramarmos sangue inocente, Capitão? Isso vai pesar nas nossas mãos, na nossa consciência.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Então o sangue estará tanto nas mãos deles quanto nas nossas, se não mais. Que isso te conforte. O mais importante é que nossas intenções eram puras – eliminar o inimigo da pátria\nAgora me ajude, Charlie, ainda precisamos fazer parecer um ataque holandês.";
			link.l1 = "Sim, senhor...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Graf_Sheffild_25");
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Então, deixamos falsas evidências para parecer que foram os holandeses. Richard e eu nunca mais falamos sobre aquele dia.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Bem, agora muita coisa faz sentido. Acho que algum parente ou aliado do Conde está por trás da morte do Richard. Mas por que ir atrás de você? Você era só um canhoneiro, não tomou nenhuma decisão naquele dia maldito.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "De fato. Isso é coisa suja e fede. Talvez alguém tenha descoberto e resolveu vingar o Conde. Mas será que um canhoneiro vale tanto esforço? Dinheiro, mercenários, contratar Raposas do Mar... Não faz sentido, Charlie.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Talvez essa pessoa esteja caçando todo mundo da antiga tripulação do Richard. O que acha, senhor?";
			link.l1 = "Acho que devemos nos afastar de Antígua, e quanto antes, melhor.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Eu também já me fiz essa pergunta, Capitão, mas ainda não encontrei uma resposta.";
			link.l1 = "Merda. Alguém está vindo. Eu pedi pra não ser incomodado!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_103");
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles!..";
				link.l1 = "O que foi, Helen??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, eu lembro que você me pediu para não deixar ninguém entrar e para não incomodar você e o Charlie, mas...";
				link.l1 = "... você decidiu vir pessoalmente. Tudo bem, tudo bem, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Um navio de guerra inglês! Foi avistado há algum tempo. No começo, não dei importância, mas ela vai nos alcançar a qualquer momento! Nunca vi um navio tão rápido.";
				link.l1 = "Então obrigado por me avisar. Espero que tenhamos tempo para nos preparar antes que ela se aproxime. Helen, Charlie, aos postos de combate!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... vocês podem continuar essa reunião secreta depois. Um navio de guerra inglês está vindo na nossa direção. Achei que era importante.";
				link.l1 = "Bem, vou dar uma olhada. Obrigado, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Capitão, um navio rápido está vindo na nossa direção. Muito rápido. Os espíritos sussurram para mim que as intenções deles não são boas.";
			link.l1 = "Obrigado a você e aos espíritos pelo aviso. Prepare-se para a batalha, só por precaução. E passe este recado aos outros por mim.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Desculpe interromper, Capitão, mas é urgente.";
			link.l1 = "Ah, espero que seja mesmo importante, Alonso. Fale.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "Um navio inglês está se aproximando. É... o 'Mirage', capitão.";
			link.l1 = "O quê? Tem certeza absoluta? Andou bebendo de novo, hein?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Tenho certeza, Capitão – não existe outro navio como esse no Caribe, você sabe disso.";
			link.l1 = "De fato. Vou dar uma olhada eu mesmo – vamos ver se esse tal de 'Miragem' existe mesmo.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Oh... Mas ainda não acabou! Brian, aí está você! Onde diabos você se meteu?";
			link.l1 = "Isso só vai adiar o inevitável.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. Quem diria até onde você chegaria. Que pena. Eu esperava te pegar desprevenido neste navio.";
			link.l1 = "Você sabe quem eu sou? Então, é você quem está por trás dos nossos últimos problemas – parece um passarão que foi tirado do ninho e teve que aparecer em pessoa, em vez de mandar outro abutre.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Certo, em ambos os casos. Imagino que um nobre reconhece outro de longe. Coronel Thomas Lynch. Parece que chegou a hora de conversarmos como cavalheiros, em vez de tentarmos nos destruir. Quem sabe conseguimos chegar a um acordo que beneficie a ambos.";
			link.l1 = "Não posso prometer nada, mas te dou minha palavra de nobre que pelo menos vamos conversar como pessoas civilizadas, Coronel.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Muito bem. Eu nunca teria conseguido ter uma conversa dessas com o Fleetwood. Ainda assim, conseguimos algo contra ele, e ele não vai mais nos incomodar. É uma pena que não tenha dado certo com você, mas deixa pra lá.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Todo o Caribe está comentando sobre a morte do Richard. Então, foi você! E imagino que a tal vantagem que mencionou era a Abigail, não é? Aliás, o que aconteceu com ela?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Não é uma ameaça, é isso?.. Então, você matou ele? Você apoia o conde?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail? Ah, a jovem judia, a noiva dele. Mais uma vez, você provou ser alguém bastante perspicaz. Ela está viva e bem — prometemos isso e cumprimos, em troca da colaboração do Fleetwood.";
				link.l1 = "Uma bela cooperação, devo dizer. Mas por que fez isso? Você apoia o Conde?";
			}
			else
			{
				dialog.text = "Apoiador? Ah, bem o contrário. Mas veja, algumas cartas deixam de poder ser jogadas quando viram um peso para quem as segura. Infelizmente, Richard acabou se tornando uma delas.";
				link.l1 = "Entendi. Você elimina todas as testemunhas. O que aconteceu com a Abigail? Você matou ela também?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "De jeito nenhum. Muito pelo contrário. Mas o Richard sabia demais e, ao voltar para o Velho Mundo, se tornou perigoso. Ele devia ter ficado aqui, e a gente não teria tirado a vida dele.";
				link.l1 = "Você elimina todo mundo que já trabalhou pra você, coronel?";
			}
			else
			{
				dialog.text = "Quem? Ah, a noiva dele, imagino. Ela era a moeda de troca. A vida dele pela dela. Ela está bem, juro pela minha honra.";
				link.l1 = "Duvido que você saiba o que é honra, considerando o que fez, coronel.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Não vou responder a essa provocação, senhor.";
				link.l1 = "Então me responda - como você conseguiu este navio? É... a 'Mirage'?";
			}
			else
			{
				dialog.text = "Vou relevar essa ofensa porque vem de alguém que nunca precisou exercer poder ou influenciar a ordem das coisas.";
				link.l1 = "Falando nisso, de onde você tirou a 'Mirage'? É ela mesma?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Não exatamente. Um navio magnífico, hein? Pena que não cumpriu seu propósito contra você. Você conhece a história deste navio, Capitão de Maure?";
			link.l1 = "Você está falando do navio fantasma e da caçada aos mercadores ingleses?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "Isso? Ah, não. Não estou falando de coisas conhecidas. Quero dizer coisas que ficam escondidas dos olhos. Este queche foi projetado por Johan van Merden e Lucas Rodenburg\nEsse belo casal armou uma sequência de esquemas, e o navio acabou sendo lançado do estaleiro em Havana. Tivemos sorte de conseguir as plantas originais. No fim, reconstruímos o Mirage em toda a sua glória e ainda o melhoramos, corrigindo algumas falhas do projeto.";
			link.l1 = "Que pena, como o senhor mesmo disse, isso não lhe ajudou muito, coronel.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Está achando graça? Não devia. Admito, você me superou tanto como capitão quanto como lutador. Mas ainda sou eu quem manda aqui.";
			link.l1 = "Isso é só uma bravata de quem está à beira da morte? Ou é aquela velha confiança exagerada de gente como você? O que está por trás dessas palavras?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Ótima pergunta. Pelo visto, você é mais do que um mulherengo e duelista, como diziam meus informantes. Tomei providências para qualquer desfecho deste encontro. Até mesmo aquele em que morro pela sua lâmina, bala ou uma bala de canhão perdida. Se eu morrer hoje, você e o Charlie vão se arrepender de não terem se juntado ao Fleetwood.";
			link.l1 = "Mais caçadores de recompensa? Por favor. Foi desagradável e cansativo, mas não mortal. Nós os enfrentamos antes – vamos enfrentá-los de novo.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Não tenho dúvidas. Agora vejo de novo o duelista despreocupado falando. Não são só caçadores de recompensa. Toda a força dos Sea Foxes e da inteligência naval inglesa vai desabar sobre sua cabeça como uma onda de tempestade em barco de pescador.";
			link.l1 = "O que você quer de mim? Não espera que eu me renda, né?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Claro que não. Observamos você com atenção durante todo esse tempo. Quero lhe propor um acordo que seja bom para ambos. Seria tolice recusar. E, como dois cavalheiros, espero que possamos chegar a um entendimento.";
			link.l1 = "Então eu repito a pergunta, Coronel, o que o senhor quer? Suponho que seja sobre o Charlie?.. E acha que pode me oferecer algo em troca? Eu não vou trair por algumas moedas de ouro.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Correto de novo. Não se trata só de algumas moedas de ouro, como você disse, mas de uma verdadeira montanha – 10.000 dobrões. O depósito estará esperando por você no banco em Port Royal, caso cheguemos a um acordo\nMas o mais importante que eu ofereço é a sua vida, capitão de Maure. Você me ouviu. Vamos encerrar toda a perseguição se todos nós baixarmos as armas agora e você entregar o Charlie para nós\nJá ouviu a expressão 'o homem contra a sociedade'? No seu caso, se recusar, será 'o homem contra o Estado'. Decida, Charles. Aqui e agora.";
			link.l1 = "Você pode até usar seu título e influência pra intimidar um ou outro idiota. Mas eu não sou idiota. E sinto o cheiro do desespero de longe. Vai embora. E agradeça por eu não ter te matado – você merece muito mais do que isso.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Você não precisa realmente do Charlie, Coronel. Você precisa é do silêncio dele.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "Eu aceito isso pela segurança minha e dos meus homens, não por ganância pelo seu dinheiro, só pra deixar claro.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Você acabou de tomar uma das piores decisões da sua vida, Capitão de Maure. Não queria estar na sua pele. Sinceramente. Depois não diga que não foi avisado – ninguém vai te fazer uma proposta dessas de novo. Muito menos eu. Adeus.";
			link.l1 = "Espere, Coronel.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "O quê, mudou de ideia? Minhas palavras finalmente surtiram efeito?";
			link.l1 = "Certo, exatamente o contrário.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "O que você quer dizer? Explique-se.";
			link.l1 = "Suas palavras só fortaleceram minha determinação contra você. Não faça essa cara – não vou te matar. E como eu disse, ainda vou te deixar ir. Mas acho que você vai se virar sem um barco.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Não preciso disso, pois já tenho um navio.";
			link.l1 = "Você está certo. Mas só quanto a não precisar disso. Pode até ser um homem influente. Mas lhe falta senso de medida. E tato. Vou fazer o que você está acostumado a fazer – assumir o controle da situação.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Você não é, Capitão de Maure. Não se engane.";
			link.l1 = "Totalmente? Talvez não. Mas você também não está, coronel – agora sua vida está nas minhas mãos. Não importa o que aconteça comigo depois – agora eu posso fazer o que quiser. E eu... fico com este navio. Você está livre. A costa não está longe.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Você não teria coragem. Mas, pelo seu olhar... Aproveite sua pequena vitória. Você conseguiu...";
			link.l1 = "Sim, sim, uma das piores decisões da minha vida. Já ouvi isso antes. Fora deste navio. Do meu navio. Vai pular sozinho, ou quer que a gente te jogue ao mar?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_7");
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Eu nunca imaginei que veria ele assim – humilhado, pulando pela janela e nadando até a praia de quatro.";
			link.l1 = "Deu uma olhada? Satisfeito? Ótimo. Você é o próximo.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "What are you saying, sir? We're not enemies; I was just following orders!.. Can I at least ask for a boat? You'll never see me again!";
			link.l1 = "Você não teria piedade de mim se estivesse no meu lugar e tivesse acabado de perder uma batalha para você. Então agradeça por eu não ter te matado. Pela janela. Agora. Quem sabe você alcança o seu protetor.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Prefiro morrer a passar por uma humilhação dessas, monsieur!";
			link.l1 = "Como quiser.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "Aquele era o Coronel, não era, Capitão?";
			link.l1 = "Certo. Olhe pela janela, Charlie, você não vai se arrepender.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_13");
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "O Coronel?.. Nunca imaginei que veria algo assim, senhor. Que alguém teria coragem de jogar um homem com um título desses ao mar como se fosse um marinheiro qualquer! Richard jamais faria isso – respeitar a hierarquia era parte fundamental dele.";
			link.l1 = "Isso foi enfiado nele depois de anos de treinamento. Ele é um homem militar, com a mentalidade que vem junto. Eu não sou assim, penso de forma mais ampla, sem essas... limitações.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "E a gente não vai se meter em encrenca por fazer isso com ele?";
			link.l1 = "Heh, você culpa o Richard, mas pensa igual a ele. Nós ousamos resistir, então vão nos caçar por um tempo. Mas, cedo ou tarde, até a marinha inglesa vai desistir de nós. E para o Lynch, isso vai virar uma questão pessoal. Mas garantimos que, da próxima vez, ele não vai ter os recursos do Estado ao lado dele.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Sabe, Capitão, a partir de hoje, te respeito ainda mais. Nunca vou me arrepender de não ter ido embora com o Dick na Valkyrie e de ter decidido ficar ao seu lado.";
			link.l1 = "Obrigado, meu amigo! Prepare-se – a tempestade está se formando sobre nós. Mas sabe de uma coisa? Algo me diz que vamos sair vitoriosos de novo. Vamos, está na hora de voltar ao convés.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "Isso não é totalmente verdade, embora pessoalmente eu não me importe com o Charlie se ele ficar de boca fechada daqui pra frente. Mas meus colegas querem ver o corpo dele. E eles sabem como ele é\nIsto é a vida real, Charles, não um conto de fadas infantil ou um poema de cavalaria lido por babás quando éramos crianças, e eu não vejo uma solução que agrade a todos.";
			link.l1 = "Mas eu faço. Sempre se pode encontrar um corpo parecido. E comprar roupas parecidas. Subornar quem for preciso. E eu vou conversar com o Charlie. E te dou minha palavra como garantia.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				dialog.text = "É... um grande risco. E não se trata só de confiar na sua palavra. Mas também se meus colegas vão acreditar em mim quando virem um corpo parecido com o do Charlie. E eu não vou correr esse risco... assim, de qualquer jeito.";
				link.l1 = "Quanto?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				Notification_Reputation(false, 71, "low");
				dialog.text = "A palavra de um homem com a sua reputação? Só pode estar brincando. Nobreza de sangue não basta para confiar.";
				link.l1 = "Ouvindo isso de outro homem com origem e feitos parecidos, me perdoe, Coronel.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Você está certo, claro. Mas, neste caso, trata-se da minha confiança, não da de mais ninguém. E você, como fiador, não me serve\nVou dizer só mais uma vez. Me entregue o Charlie. A não ser, é claro, que queira acabar como o Fleetwood.";
			link.l1 = "Você pode até usar seu título e influência pra intimidar um ou outro idiota. Mas eu não sou idiota. E sinto o cheiro do desespero de longe. Cai fora. E agradeça por eu não ter te matado – você merece muito mais do que isso.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Finalmente, direto ao ponto. Um milhão de pesos. Oferta final.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Eu vou te pagar o dinheiro. Não pense que sou pobre ou que não dou valor à vida dos meus homens. Nenhuma dessas coisas é verdade. Pegue.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " Você tem um bom apetite, embora eu não esperasse menos. Mas agora, eu não tenho tanto assim, e...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Sem prata - sem acordo. Achou que eu teria piedade? Por acaso pareço um santo, senhor?";
			link.l1 = "Mas talvez você pudesse esperar um pouco? Onde e quando seria conveniente para você nos encontrarmos de novo? Eu posso pegar os dobrões emprestados com um agiota.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "Então você acha que eu sou ainda mais ingênua do que pensei\nNão sou uma camponesa disposta a esperar para sempre por alguém que já conseguiu o que queria comigo\nSem dinheiro? Eu nunca pedi mesmo. Só quero o Charlie. Você não me serve pra nada, apesar de todo o problema que já causou.";
			link.l1 = "Você pode até usar seu título e influência para intimidar um ou dois tolos. Mas eu não sou tolo. E sinto o cheiro do desespero de longe. Saia daqui. E agradeça por eu não ter te matado – você merece muito mais do que isso.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Você está mesmo tão apegado ao pobre Charlie? De qualquer forma, sua nobreza merece respeito. Certifique-se de que seu artilheiro seja mais silencioso que um túmulo. Ou vocês dois vão acabar lá.";
			link.l1 = "Eu prometo. E você cumpre sua palavra e encerra toda perseguição.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Eu também prometo. E mais uma coisa. Apesar da sua vitória justa, vou levar meu navio comigo. Ele foi feito sob medida, sabia? E custou caro.";
			link.l1 = "E o direito do vencedor? Mas não vou abusar da sorte. Desta vez.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_FadeLong("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Quase me dói dizer isso, Brian, mas receio que nossa parceria termina aqui.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Eu... estou livre, coronel? Vai retirar a recompensa pela minha cabeça, e eu poderei recomeçar como se fosse um homem de bem?";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Eu diria que você já viu demais – assim como o falecido Fleetwood. Acabei de receber um suborno bem na sua frente.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "Eu... eu não vou contar nada pra ninguém, juro por Deus!";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "É claro que não vai.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "Não!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Não me olhe assim, Charles. Se eu ficar me preocupando o tempo todo se o Brian vai abrir o bico, não vou conseguir dormir nunca.";
			link.l1 = "Nem sei se devo me surpreender com o que vi ou não.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Você não deveria. Eu estou comprometido. Tudo o que peço de vocês dois é que fiquem de boca fechada sobre o que aconteceu. Vou tentar encontrar um corpo parecido, arrumar o rosto direito, fazer bom uso do dinheiro e convencer meus colegas.";
			link.l1 = "Obrigado, coronel.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Ainda não tem pelo que me agradecer. Sempre existe o risco de não acreditarem em mim, e aí a caçada recomeça. Por enquanto, adeus, Capitão de Maure. Vou zarpar no meu navio. Sem reclamações aqui – já fiz um grande favor pra você e pro Charlie.";
			link.l1 = "Bem, então adeus.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_LT_25");
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Você ao menos sabe com quem estava falando, Capitão? Um coronel! Foi ele quem armou toda essa confusão?";
			link.l1 = "Eu sei, ele se apresentou. E você está certo - ele era mesmo.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "É estranho, senhor, porque eu já o conheci como superior do Richard. Como isso é possível? E por que ele está indo embora como se nada tivesse acontecido? Afinal, o que ele queria?";
			link.l1 = "Na verdade, não há nada de estranho nisso. Quem executa ordens duvidosas costuma arriscar a vida não tanto pelos inimigos, mas pelos próprios superiores. E ele queria a sua cabeça, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Eu não entendo, Capitão. Então por que ele está indo embora? Ele aceitou a derrota?";
			link.l1 = "Isso não é nada parecido com ele. Tive que dar a ele ouro pesando quase tanto quanto a sua cabeça. Talvez até um pouco mais. Um milhão de pesos, pra ser exato.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "E você... pagou aquela quantia absurda? Por mim?..";
			link.l1 = "Bem, não só por você. Por mim também. E por todos os rapazes, claro. Mas sim, Charlie, principalmente por você. Se tivéssemos matado ele, depois seríamos caçados por expedições punitivas para sempre.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "Eu... não acredito nisso, senhor. Só... obrigado. Eu não achei que Fleetwood faria isso no seu lugar.";
			link.l1 = "Você está sendo duro demais com ele depois da fuga. O Richard só queria uma vida tranquila com a Abigail. Sinto muito que não tenha dado certo pra ele. Além disso, ele cumpriu a palavra e pagou sua dívida. Heh, eu, Fleetwood — você realmente tem sorte com seus capitães, hein, Charlie?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "Sem brincadeira, Capitão. Então, acabou tudo agora?";
			link.l1 = "Sim, meu amigo muito valioso. Pelo menos por enquanto. A briga acabou – pode avisar aos rapazes para guardarem as armas. E peça para se prepararem para içar as velas.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Não me importa o motivo do seu acordo – seja por ganância, medo ou dever com seus homens. O importante é que você concordou. Vou mandar meu homem para Port Royal com instruções para o banqueiro.";
			link.l1 = "Tá bom. Mal posso acreditar que isso finalmente acabou.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "Sabe de uma coisa, que se dane o dinheiro. Sempre dá pra conseguir mais. Tem outra coisa que eu quero de você em troca do Charlie, Coronel.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Oh? Preciso admitir, você me surpreende, Capitão de Maure. E o que, na sua opinião, seria equivalente à careca do velho canhoneiro, se uma montanha de ouro não te agrada?";
			link.l1 = "Você mesmo disse – um navio magnífico, com os defeitos de projeto corrigidos. Estou ansioso para testá-lo eu mesmo. Você ainda tem as plantas. Mas só existe um Charlie. Além disso, é do seu interesse me manter satisfeito.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				dialog.text = "Você é um negociador duro. Tem ideia de quanto nos custou construir só um desses?";
				link.l1 = "(Confiável) (Honra) Eu sei muito bem, por isso pergunto. Sua mão está na minha boca até o cotovelo. Pode tentar atirar nesse lobo. Mas vai perder a mão. E não só ela.";
			}
			else
			{
				dialog.text = "Receio que construir uma dessas custe muito mais do que o ouro que separamos para você. Mas você me divertiu, Charles. De um jeito bom.";
				link.l1 = "Valeu a tentativa.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Vejo que você sabe o que quer e corre atrás dos seus objetivos na vida\nMuito bem. O quetche é seu. Mas esqueça o dinheiro – o agiota vai dizer que não sabe de nada.";
				link.l1 = "Por mim, tudo bem.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Com certeza. Minha vida sempre foi feita de agarrar oportunidades e me proteger dos riscos\nEntão traga o Charlie aqui, e nos separamos em paz. Depois disso, pode até ficar com o depósito. Mas eu vou embora neste navio.";
				link.l1 = "Então vamos resolver isso.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Não posso dizer que estou completamente satisfeito. Mas quero acabar com isso logo. Agora me dê o que eu quero.";
			link.l1 = "Não é 'o quê', mas 'quem'. Mas como preferir.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Nem eu. Estou começando a achar que não se trata só do que um homem é, mas de quem ele tem ao lado – um trabalho simples de capturar um velho canhoneiro virou uma dor de cabeça por causa do capitão dele, ou seja, você, Charles\nChame o Charlie aqui. Essa confusão vai acabar de uma vez – vamos içar âncora e cada navio segue seu rumo.";
			link.l1 = "Partir, é isso que você diz?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Parece surpreso? Achou mesmo que o quetch era seu prêmio legítimo? Nós não somos piratas, Capitão de Maure. Pessoas civilizadas seguem regras diferentes, muito mais complexas. O navio fica comigo.";
			link.l1 = "Então tá...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "Está tudo bem com o senhor? Aquele é... o coronel?";
			link.l1 = "Sim, Charlie, é o coronel. Você chegou na hora certa – eu já estava prestes a ir te buscar pessoalmente.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Me buscar, Capitão?.. Agora mesmo? Por que ficou tanto tempo conversando com esse... homem? Achei que estivesse em apuros, então vim pessoalmente.";
			link.l1 = "Certo. Ainda estamos em apuros apesar da vitória. E continuaríamos assim se o coronel e eu não tivéssemos encontrado uma solução.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Conseguiu convencer ele a nos deixar em paz, senhor?";
			link.l1 = "Infelizmente, só eu. Não nós. Você... vai com ele, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "O quê?.. Mas por quê?.. Nós vencemos!";
			link.l1 = "Você não entende? Não dá pra continuar vencendo sempre – eles não vão parar até conseguirem a sua cabeça.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Não acredito que você está fazendo isso com o velho Charlie, Capitão. Você é igual ao Dick. Os dois me disseram que eram meus amigos. E os dois me abandonaram, assim como a todos ao redor.";
			link.l1 = "Esse é o peso que um capitão carrega, a responsabilidade dele. Vejo que você não entende isso, porque tudo o que fazia era carregar os canhões com balas.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Não entendeu?.. Talvez eu só não seja um traidor como você? Sabe pra onde deveria ir?";
			link.l1 = "Pro inferno? Talvez você tenha razão. Todos nós merecemos isso.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "Vai se catar, senhor.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Hilário. Quase ri. Ouviu isso, Brian?\nÀs vezes, ouvir camponeses simples falar é até refrescante, nem irrita. Você tomou a decisão certa, Charles. Sei como isso é difícil pra você. Mas se console: agora nem você, nem nenhum dos seus homens vai sofrer.";
			link.l1 = "Espero que cumpra essa promessa, Coronel.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Sou um homem de palavra. O destino da Abigail é prova disso. Olhe para o Brian também. Um pirata francês, mas tomou a decisão certa quando era hora de escolher o lado certo. E ninguém encosta nele enquanto servir a nós com lealdade. Assim como ele, você está seguindo pelo caminho certo, Capitão de Maure.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "Falando em partir. Quero sair daqui o quanto antes. Nesse navio veloz, sem dúvida, que você me prometeu, coronel.";
			}
			else
			{
				link.l1 = "Eu não sou um pirata. E também não pretendo me juntar à frota inglesa tão cedo. Mas faço questão de receber a recompensa prometida.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "I won't hide it - it feels like tearing her from my heart. I'll have to spend on a new one, but perhaps it's worth it - too long have I been troubled by the thought that Charlie might spill the beans\nIf you don't talk or commit serious crimes against England, consider that we're no longer enemies. Enjoy the new ship; she's indeed beautiful. Goodbye, Charles. Brian - prepare a boat for us. Charlie - follow me as you have no say in the matter.";
				link.l1 = "Adeus. Todos vocês.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "Uma pena, sempre precisamos de gente capaz, não importa a nacionalidade. Mas é claro, você ainda merece a recompensa. Pode ir tranquilo para Port Royal — eu vou chegar lá antes de qualquer outro navio nesse queche.";
				link.l1 = "Espero que sim. E espero que não tenha uma escolta armada me esperando em Port Royal.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Duvidando da minha palavra de novo? Que vergonha. Você ganhou a gratidão de toda a marinha inglesa. Se algum dia precisar de algo, ou decidir se juntar a nós, me procure, Capitão de Maure.";
			link.l1 = "Uma vez, tentei conseguir apoio e contatos com a inteligência inglesa. Não deu certo. Então adeus, Coronel.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
