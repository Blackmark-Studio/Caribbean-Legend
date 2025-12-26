// диалоги НПС по квесту 'В поисках Стража Истины'
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Como posso ajudar você?";
			link.l1 = "Desculpe, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "O que você quer? Outro interrogatório? Vete al diablo!";
			link.l1 = "Senhor, qual é o seu nome?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "O que diabos te importa o nome do homem que você vai enforcar ou fuzilar? Bastardo! No fim das contas, fui descuidado o bastante pra cair nas suas mãos...";
			link.l1 = "Senhor, identifique-se. Não posso conversar com um homem sem saber o seu nome.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". Pronto, satisfeito? Agora, com quem tenho o prazer de falar?";
			link.l1 = "Meu nome é "+GetFullName(pchar)+". Já ouviu falar de mim antes?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "Não, carajo! Por acaso eu pareço alguém que conhece todo vagabundo que anda solto nas Índias Ocidentais que...";
			link.l1 = "Chega. Vamos resolver isso sem insultos e agir como verdadeiros cavalheiros. Seu destino vai depender do que você puder me contar. Se me disser algo interessante, vou pedir sua libertação sob minha responsabilidade. Assim você pode escapar da bala de mosquete ou da forca que te aguardam neste momento.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Dios mio, essa é uma oferta irrecusável. O que você gostaria de saber, senhor?";
			link.l1 = "Quem organizou um ataque tão grande contra St. Pierre e por quê?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Barão Ramon de Mendoza y Riba, comandante da guarnição da Ilha da Providência. Ele enviou um esquadrão para atacar e saquear a cidade, levando qualquer coisa de valor que encontrássemos.";
			link.l1 = "Qual era sua tarefa imediata durante o ataque? Especificamente, quais foram suas ordens?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Sou o comandante do batalhão naval. Nossas ordens eram tomar o forte e garantir o controle das baterias para impedir que atirassem em nossos barcos de desembarque enquanto se aproximavam da cidade. Depois disso, meus homens participaram do ataque a St. Pierre.";
			link.l1 = "Você foi informado sobre os objetos de valor que estão na cidade? Sobre a quantidade e a qualidade deles?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Não tínhamos informações exatas sobre a quantia, mas o Barão de Mendoza y Riba nos disse que há prata guardada sob o forte e que os armazéns do porto têm matérias-primas estratégicas vitais para o esforço de guerra: pau-ferro e seda naval.";
			link.l1 = "Você encontrou aqueles objetos de valor?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "Não. Não encontramos nenhum dos dois. Os armazéns estavam cheios de mercadorias coloniais comuns, e sob o forte havia pólvora, armas e chumbo. Mas não tivemos tempo suficiente para fazer uma busca mais detalhada... os reforços franceses chegaram com tudo e fomos obrigados a lutar.";
			link.l1 = "Você não achou estranho não ter encontrado os objetos de valor?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Claro que sim, mas normalmente não questiono ordens.";
			link.l1 = "Escute o que vou lhe dizer. O Forte St. Pierre nunca guardou prata, e aqueles armazéns jamais armazenaram pau-ferro ou seda. Pense bem, señor, antes de responder, porque se sua resposta não me agradar, vou me virar e sair daqui, deixando você ao seu destino... um destino lamentável.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Estou ouvindo.";
			link.l1 = "Eu não acredito que o único objetivo do seu ataque tenha sido um simples roubo. St. Pierre é uma colônia discreta e relativamente pobre para justificar o envio de um esquadrão inteiro, liderado por um navio de linha de primeira classe. Com certeza você, seu comandante ou alguém mais recebeu ordens ou instruções adicionais. O que te disseram? Pense bem antes de responder...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Vai ficar quieto? Tudo bem. Pense um pouco, eu espero.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Senhor, a minha vida depende da minha resposta?";
			link.l1 = "Certo.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "Eu tenho algo... Mas você precisa me jurar que vai me tirar daqui e pagar meu resgate de volta para a Espanha.";
			link.l1 = "Se você me disser algo que valha a minha atenção, juro pela Santa Cruz que você será levado ao meu navio para resgate e será poupado da execução.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "Certo. Dom Diego de Montoya ordenou ao nosso batalhão de fuzileiros que devemos, com máxima discrição e urgência, encontrar e capturar um homem chamado Miguel Dichoso, que está em algum lugar de St. Pierre sob a proteção das autoridades.";
			link.l1 = "Continue. Quem é Diego de Montoya?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "O oficial no comando do esquadrão. Ele fugiu logo após a sua... chegada dramática.";
			link.l1 = "Quem é ele, esse Dom Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "Eu só sei que ele é o representante autorizado do Barão de Mendosa y Riba, seu braço direito e encarregado das tarefas mais importantes.";
			link.l1 = "Interessante... E quem é Miguel Dichoso, o homem para quem toda essa catástrofe aparentemente foi armada para pegar? Deve ser um sujeito perigoso, hein?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Você se lembra do seu juramento, señor?";
			link.l1 = "Sim. E garanto que, se continuar contando sua história, vou entregá-lo como testemunha-chave ao meu navio e depois... bem, vou dar um jeito de levá-lo até um assentamento espanhol. Mas só depois que me contar tudo o que sabe.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso é um antigo companheiro de armas do barão, embora alguns digam que Miguel o traiu. O senhor de Mendoza y Riba o quer vivo, então recebemos ordens de não matar Dichoso sob nenhuma circunstância.";
			link.l1 = "Dichoso também é espanhol?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Sim. Don Diego de Montoya nos deu uma descrição aproximada e ordenou que qualquer homem parecido com Dichoso fosse entregue diretamente a ele. Mas, como tivemos pouco tempo antes do seu contra-ataque, nunca tivemos a chance de procurar.";
			link.l1 = "Você conhecia o Dichoso pessoalmente?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "Não, só de fama. Nunca vi esse homem antes. Alguns dos meus colegas oficiais o conheciam pessoalmente. Todos eles estão mortos.";
			link.l1 = "Quão gravemente o Dichoso traiu seu Don Mendoza para que ele decidisse mandar um esquadrão inteiro atrás dele?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "I will tell you. The baron only recently arrived in the Caribbean from Spain. His orders were to ensure the safety of the Spanish Treasure Fleet convoys, but instead he looked inland... searching for Indian gold. His head was turned by rumours of hidden treasure. He decided that an ancient Maya city exists somewhere deep in Yucatan's jungles - Tayasal, the legendary city of gold\nThe baron sent several expeditions to find the city, but all of them were utterly vanquished in the wild selva. No doubt each and every one of them was slaughtered by the martial Itza people who live there\nEventually, Inquisitor Vincento had enough of Don Mendosa's fantasies and the pointless deaths of good soldiers. The inquisitor informed Madrid about the situation. The viceroy forbade Don Mendosa to search for the mythical city and ordered him to focus on his duties. That's when Miguel Dichoso showed up\nHe convinced the baron to organise another expedition, which, surprisingly, was a success. They found ruins of an ancient city and a pile of gold encrusted with jewels. But on their return, they were attacked by the Mosquito tribe\nAll except Miguel perished; the Indian darts are dipped in some local poison, even a small scratch leads to certain, agonising death in a few days. Dichoso returned to Providence with what treasure he could carry\nCarajo! The baron was unspeakably happy, he sent urgent letters to Madrid and to Father Vincento in Santiago; no doubt he wanted to rub his success in the Reverend Father's face. Then a frigate was prepared to deliver the treasure back to Spain. Dichoso volunteered to escort it.";
			link.l1 = "Deixa eu adivinhar. Ele não entregou o ouro?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Correto, señor! A fragata sumiu sem deixar rastros, junto com toda a carga e a tripulação, incluindo Dichoso. O barão ficou furioso. Mais uma vez foi humilhado diante do Escorial, para grande satisfação do padre Vincento. Agora Dom Mendosa é um homem obcecado em recuperar seu orgulho ferido, seu tesouro perdido e Miguel Dichoso.";
			link.l1 = "Não é possível que a fragata tenha simplesmente sido pega por uma tempestade e afundado? Ou capturada por piratas?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "O barão jurou, no calor do momento, que tinha certeza de que Dichoso o havia traído. Não sei os detalhes. Algumas semanas depois, Dom Diego de Montoya chegou com novas informações de que Miguel Dichoso poderia estar em St. Pierre.";
			link.l1 = "Hm. Interessante. Esses tesouros indígenas de novo. Tudo parece suspeitamente ligado a eles... Então, você não encontrou o Dichoso?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "Não. E, sinceramente, eu ficaria surpreso se ele algum dia tivesse vindo aqui. O barão está tão obcecado com a ideia de capturar Dichoso que acreditaria até nas fantasias mais absurdas.";
			link.l1 = "Me conte, "+npchar.name+", como é que Dom Mendosa descobriu sobre essa... ahn... cidade de Tayasal? Não foi invenção dele, né? Tinha alguma prova ou algo assim?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "Foi o padre Vincento quem primeiro ouviu falar sobre a suposta existência de Tayasal e da cidade de ouro. Onde ele descobriu isso, eu não faço ideia...";
			link.l1 = "Que reviravolta interessante. O padre Vincento teve sozinho a ideia da existência de Tayasal, avisou a Espanha pessoalmente e começou a jogar areia no caminho do barão...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "Como um bom católico, você deve saber como esses reverendos padres do Santo Tribunal agem... Ele não avisou Madri à toa. Ele tem algum interesse nisso, mas a chegada do barão aparentemente não fazia parte dos planos dele. Enfim, não sei mais nada sobre isso. Nunca tive vontade de me meter com a Inquisição.";
			link.l1 = "Certo. Você me deu muitas informações interessantes, "+npchar.name+", e fiel ao meu juramento, vou tirar você daqui. Voltarei para te buscar depois, mas por agora... deixe-me pensar um pouco sobre o que você me contou...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Senhor? Vai cumprir sua promessa?";
			link.l1 = "Sempre cumpro minhas promessas. Hoje é seu dia de sorte, "+npchar.name+". Você vem comigo para Santiago, em Cuba. Vou te contar mais sobre meu plano quando chegarmos. Mas, por enquanto, seja bem-vindo a bordo. Você será escoltado até o porto e levado ao meu navio.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "Minha gratidão, capitão. Fico feliz que seja um homem de palavra.";
			link.l1 = "Você pode agradecer depois. Você será meu convidado, mas sob escolta. Não leve para o lado pessoal, ainda preciso de você.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Eu entendo, senhor. Dou-lhe minha palavra, como oficial espanhol, de que não tentarei escapar.";
			link.l1 = "Deus protege os cautelosos. Te vejo a bordo.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Capitão, quais são suas intenções aqui em Cuba? Veio só para me deixar? Mal ouso ter essa esperança...";
			link.l1 = "Isso mesmo, estou aqui para levar você de volta aos seus compatriotas. Agora, o motivo da minha chegada aqui é um pouco mais complicado do que só isso. Mas isso já não diz mais respeito a você. Vou deixar você ir agora mesmo, sem pedir resgate, mas com a condição de que me jure duas coisas.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "O que são eles?";
			link.l1 = "A primeira coisa é que vou te entregar uma carta lacrada. Você vai levar essa carta pessoalmente ao Inquisidor de Santiago, Padre Vincento. Se ele perguntar de quem é a carta e como você a conseguiu, diga a verdade...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "A segunda condição é que você não vai ajudar nem colaborar com qualquer tentativa de me encontrar ou atacar meu navio, pelo menos por uma semana. Concorda?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "É só isso?";
			link.l1 = "Sim, é só isso. Cumpra minhas condições e você está livre para ir.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Eu juro a você, señor, que entregarei a carta pessoalmente ao Padre Vincento e que não tomarei nenhuma atitude que possa provocar a agressão da guarnição de Santiago contra você ou seu navio. Pode ficar tranquilo, cumprirei minha palavra. Sou espanhol e respeito adversários fortes e nobres.";
			link.l1 = "Tudo bem, Don "+GetFullName(npchar)+", eu aceito seu juramento e vou deixá-lo ir agora mesmo. Aqui, pegue esta carta para o Inquisidor. Você está livre.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Adeus, senhor. Espero que nunca mais nos encontremos no campo de batalha. Isso me entristeceria profundamente.";
			link.l1 = "Adeus...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dios mio, que encontro mais afortunado! Olá, monsieur "+GetFullName(pchar)+"! Vejo que você se tornou um hóspede bem-vindo em Santiago. Está trabalhando para a Santa Inquisição?";
			link.l1 = "Saudações, señor "+npchar.name+". Eu achei que nunca mais fôssemos nos ver, pelo menos não em circunstâncias amigáveis! Não, só passei para visitar o Padre Vincento. E você? Agora está servindo em Santiago?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "After you freed me from arrest, I was compelled to stay in Santiago; it is not safe for me to return to Providence... but as you can see, I've kept my word. No Spanish ships in hot pursuit of you...";
			link.l1 = "Fico feliz que nós dois sejamos homens de palavra.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Escute, capitão, se não se importa, que tal erguer um copo de rum pelo nosso reencontro, por assim dizer? Nunca imaginei que faria esse convite a um francês, mas você, senhor, é uma exceção.";
			link.l1 = "Claro! Não me importaria de enxaguar a boca com um pouco de rum. Vamos para a taverna.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ah, saúde!";
			link.l1 = "A que brindamos, senhor oficial?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Vamos brindar a algo neutro, mas que nos diz respeito. Por exemplo, ao serviço valente e bem-sucedido à nossa pátria! Cada um tem a sua!";
			link.l1 = "E vamos também brindar para que nossos monarcas cheguem a um acordo entre si, e para que franceses e espanhóis parem de brigar tanto em casa quanto no Caribe.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Muito bem dito, capitão! À paz! Vou te mostrar como se bebe à espanhola! Arriba, abajo, al centro e pra dentro!";
			link.l1 = "À paz... (bebendo)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha! O rum cubano realmente é o melhor do Caribe...";
			link.l1 = "Concordo. Me diga, tentaram te punir por ter sido capturado em St. Pierre?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Por sorte, só levei uma advertência leve. Todo aquele desastre ficou para trás. No fim das contas, eles precisam de oficiais aqui nas colônias.";
			link.l1 = "E o seu comandante... como era o nome dele... Diego, não é? Como foi pra ele aquela incursão fracassada? Acabou sendo rebaixado?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Ah, não! Nosso querido Diego de Montoya é intocável enquanto tiver Don Ramon de Mendosa y Riba por trás dele. Aliás, Don Diego estava em Santiago ontem mesmo. Ele chegou de San Jose.";
			link.l1 = "É mesmo? Que interessante! Ainda bem que não nos encontramos na rua. Acho que essa história teria acabado em um duelo, haha!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Dom Diego não tem tempo para você agora, capitão. Ele tem coisas demais em jogo neste momento para arriscar a vida em um duelo. Ele armou algum plano junto com o Barão Mendoza no Main Ocidental. Reuniu um esquadrão em Havana e está pronto para zarpar de volta para a Espanha a qualquer momento.";
			link.l1 = "Você também faz parte da tripulação dele?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "Não. Amanhã parto para a guarnição em San Juan, que fica em Porto Rico. Não sou mais bem-vindo em Providence com Don Mendosa lá.";
			link.l1 = "Então vamos brindar à sua nova missão, e que só te esperem bons momentos e belas mulheres por lá.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Muito obrigado, monsieur. Também lhe desejo tudo de bom. Ah, acho que está na hora de eu ir. Vou terminar esta bebida e então me despedir de você.";
			link.l1 = "Vá com Deus, senhor "+npchar.name+". Talvez a gente se encontre de novo em tempos de paz.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Just as I told you, Don Diego: the fish took the bait; hook, line, and sinker... Oh, looks like we meet again, monsieur. Unfortunately, not under the peaceful auspices that we wished.";
			link.l1 = ""+npchar.name+"? Ora! Não esperava por isso. Por algum motivo, achei que você fosse um oficial honesto e nobre. Parece que me enganei.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "O que te faz pensar que você está certo? Eu cumpri minha palavra, nunca jurei amizade eterna a você. Nada mudou, monsieur. Você continua sendo inimigo da Espanha e meu inimigo pessoal. Aqui não é Santiago, não tem nenhum Padre Vincento, e aquela cartinha de salvo-conduto dele não vai te ajudar...";
			link.l1 = "Ah, é mesmo? Pois eu acho que puxar conversa amigável tomando um rum, enquanto tenta me atrair pra uma armadilha, é bem traiçoeiro, não acha, señor "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Você ousa me chamar de traidor, seu maricón?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "Ei, você! Isso, isso, você! "+GetFullName(pchar)+"?";
			link.l1 = "Sim, sou eu.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "Recebi uma carta de uma pessoa importante. Você já sabe quem é.";
			link.l1 = "Eu sei, me dá isso aqui.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Aí está. Que tal algumas moedas pelo meu trabalho?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Pegue um pouco de prata. Você ganhou isso honestamente.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Tá tentando me passar a perna, é? Você já foi pago pela entrega.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Obrigado, rapaz. Foi um prazer lidar com um cavalheiro tão generoso.";
			link.l1 = "Certo, suma daqui, e nem pense em contar o que aconteceu aqui.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "O Lobo de Havana é seu amigo...";
			link.l1 = "Hã? Você ainda está aqui...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Bem-vindo a bordo do 'Admirable', Capitão "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! Surpreendente. Você me conhece?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Quem nas colônias francesas nunca ouviu falar do grande capitão chamado "+GetFullName(pchar)+", aquele que quebrou os dentes de um esquadrão espanhol liderado por um couraçado atacando St. Pierre e acabou com todo o grupo de invasores inimigos! Você é um herói nacional!";
			link.l1 = "Ah, qual é. 'Um herói'... Sou só um soldado cumprindo seu dever com a França.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Não acho que muitos soldados conseguiriam fazer o que você fez, capitão... Olha, eu até queria te pagar um rum na taverna, mas infelizmente: o capitão proibiu os homens de beberem até uma gota de rum, e eu não quero dar mau exemplo...";
			link.l1 = "Hm... Então você mesmo não é capitão?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "Eu pareço um capitão? Hoho! Não, sou só o contramestre. Meu nome é Serge Degas. Nosso capitão, Gaius Marchais, passa o dia inteiro na taverna, enquanto a gente fica aqui esperando por uma tal 'caravana' de mercadores. O capitão está devendo salários aos marinheiros, e pra nós também, a tripulação toda está sem um tostão no bolso... ";
			link.l1 = "O que foi? A caravana espanhola da baunilha ainda não apareceu pra ser depenada?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "De jeito nenhum! Nosso capitão largou a pirataria depois que capturou este galeão. Veja só, ele ouviu dizer que uma caravana de comércio indo para a Europa faria uma parada em Guadalupe em breve, e que eles comprariam baunilha. Então ele encheu nossos porões até a tampa de baunilha em Bridgetown! Achou que conseguiria vender cada caixa por trezentos pesos — sim, só que não!\nClaro, quando chegamos lá, não havia caravana nenhuma, e vender baunilha para os locais seria prejuízo na certa. Então aqui estamos, esperando esses 'mercadores' — tenho certeza de que eles vão aparecer um dia, ou daqui a três anos... O Capitão passa o dia inteiro na taverna, enchendo o saco de todo mundo. Só volta pro navio pra desmaiar. Agora, finalmente, ele está disposto a vender por duzentos pesos só pra não sair no prejuízo.\nTodo nosso dinheiro foi nesse carregamento. Qualquer dia desses, a tripulação vai amarrar ele e vender a baunilha por qualquer preço só pra pagar as dívidas... Juro, já estou até vendo isso acontecer a qualquer momento.";
			link.l1 = "Então... o que está preocupando seu capitão?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Bem, se é pra fazer um trabalho, que seja bem feito. Ele não faz nenhum dos dois. É um péssimo negociador. Seria outra história se ele também transportasse carga, mas ele queria se sentir um verdadeiro comerciante. Espero que ele caia no mar numa dessas noites...";
			link.l1 = "Eu entendo você, Serge. Não se preocupe, tenho certeza de que um dia sua... caravana vai aparecer.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Ah, eu não acredito em milagres, capitão. Quem sabe a gente se encontre de novo algum dia e tome um rum... o que eu não daria por um pouco de rum agora...";
			link.l1 = "Boa sorte, amigo.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Ei, capitão, eu bem que podia tomar um gole de rum!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Oi! Você não é do navio mercante? Não? Ah, me desculpe. Claro que não... Foi engano meu.","Não estou com disposição, monsieur, então procure outra pessoa para conversar.","Ah, você de novo?!","Hã...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Não se preocupe com isso, amigo. Acontece.","Tome um pouco de rum, capitão. Vai aliviar um pouco suas preocupações...","Não fique nervoso, amigo. Isso faz mal para a saúde.","Tá bom, tá bom. Já estou indo.",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "Argh... Mm... Mas que diabos, o que é isso?..";
			link.l1 = "Quieto, amigo... Não faça barulho...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Hã? O quê? Droga!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah! Quem é você? O que você quer de mim?";
			link.l1 = "Se você não calar a boca, eu quebro seus dentes, entendeu? Onde estão os vasos sagrados que você pegou quando tomou este navio?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Que embarcações? Eu não sei do que você está falando! Este é o meu navio!";
			link.l1 = "Seu navio? Até pouco tempo atrás, ela se chamava 'Santa Margarita' e navegava sob a bandeira espanhola... Estou te perguntando, onde estão aqueles objetos sagrados? Uma custódia de ouro, uma cruz cravejada de lazurita e um turíbulo de ouro? O que você fez com eles? Não me diga que vendeu, vendeu?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Meu Deus, não acredito no que estou ouvindo... você é espanhol? Ah, não... você não é espanhol! Você é francês! Isso é ainda pior! Você se vendeu para aqueles vis Castelhanos! Quanto estão pagando pelas almas dos franceses hoje em dia? Não vou te contar nada, traidor! Você não vai pôr as mãos nessas bugigangas!";
			link.l1 = "Nem uma palavra, hein? Tudo bem por mim. Este não é o melhor lugar para um interrogatório mesmo... Vamos amordaçar você para não gritar e depois vamos para o meu bote... você vai falar, mais cedo ou mais tarde. Não tenho dúvida disso.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Seu traidor espanhol! É melhor você...";
			link.l1 = "Silêncio, canalha... Fique logo atrás de mim ou eu te derrubo e te arrasto pelo convés pelos pés.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "Como posso ajudá-lo, senhor?";
			link.l1 = "Como vão as coisas, capitão? O que o traz a Basse-Terre? Pelo que entendi, o senhor é espanhol navegando sob bandeira holandesa?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "Qual é o problema, senhor? Sim, sou espanhol. Dá pra perceber pelo nome e pelo tipo do meu navio, mas estou aqui de forma totalmente legal. Tenho uma licença da Companhia Holandesa das Índias Ocidentais, então...";
			link.l1 = "Não se irrite, señor! Na verdade, estamos muito felizes que você seja espanhol... Me diga, você está aqui para importar ou exportar?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "Trouxe mercadorias de Havana e vendi no mercado local. Agora, estou esperando um frete lucrativo para não voltar pra casa com o porão vazio.";
			link.l1 = "Senhor, tenho uma proposta de negócio para você! Pode ganhar um bom dinheiro se me ajudar. Vamos conversar? Qual é o seu nome, aliás?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Capitão Carlos Guevara. Qual é a sua proposta?";
			link.l1 = "Preciso comprar um lote de baunilha e enviá-lo para Cuba, para um homem chamado "+pchar.questTemp.Guardoftruth.LMname+", o vigia do farol de Santiago. Mas estou com um problema sério. Para começar, nenhuma loja tem a quantidade de baunilha que eu preciso...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "Em segundo lugar, preciso partir para São Cristóvão imediatamente, e não sei quanto tempo vou ficar fora. Estou perdendo dinheiro a cada dia, entendeu? É uma droga!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Entendo. Qué lástima, señor. Não dá pra ganhar todo o dinheiro do mundo, afinal. Então, o que você quer de mim?";
			link.l1 = "Olhe ali. Está vendo aquele galeão? Ele está carregado de baunilha que eu preciso muito. O problema é que o capitão do galeão enfiou na cabeça essa bobagem de que uma caravana de especiarias vai chegar aqui logo e comprar a carga dele por um bom lucro, quase trezentos pesos por caixa!";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Yes, there are a lot of naive men around these days; a fool and his money are soon parted...";
			link.l1 = "Inocente é uma coisa, mas ele é simplesmente burro! Eu ofereci duzentos e dez pesos pela baunilha dele, aqui na loja não chega nem a duzentos. E acredita que ele mandou eu sumir? Disse que só vendia por duzentos e cinquenta!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Haha! Que idiota!";
			link.l1 = "Sim! Foi basicamente isso que eu disse a ele. Claro que ele ficou bravo comigo... mas eu realmente preciso dessa baunilha! Aqui está minha proposta, señor. Não sou comerciante, mas acho que você é um verdadeiro mestre na arte do negócio. E você tem um porão espaçoso...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Converse com esse idiota e convença-o a te vender a carga. Depois do que eu disse na cara dele, ele não vai me vender mais nada. Estou disposto a pagar duzentos e dez pesos por caixa. Se conseguir baixar o preço, fique com a diferença. E, em troca, vou fretar seu barco para levar a baunilha até Santiago.";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Quanto você está disposto a me pagar pela carga?";
			link.l1 = "Quanto você quer?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago fica bem longe... trinta mil pesos.";
			link.l1 = "Isso é demais, amigo. Vamos chegar a um acordo aqui.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "Certo, já está no meu caminho mesmo... Vinte e cinco mil e nem um peso a menos.";
			link.l1 = "Tudo bem. O capitão do galeão se chama Gaius Marchais. Ele passa o dia inteiro emburrado na taverna. Espero que você consiga convencê-lo a se desfazer de suas especiarias.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "Já fiz negócios com idiotas bem maiores antes. Vou contar pra ele todos os detalhes sobre quem anda espalhando os boatos da tal caravana que supostamente compraria a mercadoria por preços absurdos. Quando eu convencer ele de que isso tudo é coisa da cabeça dele, ele vai vender, tenho certeza.";
			link.l1 = "Então, temos um acordo?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Temos um acordo se você tiver dinheiro para pagar pela baunilha e pelo frete. Como diz o velho ditado irlandês: 'Mostre-me o dinheiro.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Aqui está, dê uma olhada. Está tudo aqui.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Tenho a prata no meu navio. Vou buscá-la e já volto!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Você trouxe o dinheiro?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Aqui está, dê uma olhada. Está tudo aqui.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Já estou pegando agora!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Estupendo! Gosto mesmo de fazer negócios com parceiros sensatos. Volte sempre "+sTemp+" até as dez da manhã. Acho que até lá nosso amigo em comum, Gaius, já terá recuperado o juízo.";
				link.l1 = "Ótimo! Até mais!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Estupendo! Gosto mesmo de fazer negócios com parceiros sensatos. Vou até a praia. Volte em três horas. Acho que até lá nosso amigo em comum, Gaius, já terá recuperado o juízo.";
				link.l1 = "Ótimo! Até mais!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Senhor, eu lembro bem do meu papel. Não se preocupe, ele pode ser difícil, mas eu vou dar um jeito nele.";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "Está feito, señor. O pobre homem ficou radiante por eu querer comprar a baunilha dele. As mãos dele tremiam de felicidade enquanto eu contava o adiantamento – ou talvez fosse só o rum mesmo. Vamos carregar a mercadoria na Praia de Capster amanhã ao meio-dia, para evitar qualquer atenção indesejada dos agentes da alfândega no porto\nAssim que a carga estiver a bordo, vou zarpar imediatamente para Santiago. Entrarei em contato com seu parceiro no farol e entregarei a baunilha para ele lá. Tem algum recado que queira que eu passe para ele?";
			link.l1 = "Sim. Aqui está uma carta. Você disse que o acordo será amanhã ao meio-dia na Praia de Capster? Muito bem, então vou ficar ancorado perto do promontório, fora do alcance da ilha caso algo aconteça.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pode confiar em mim, señor. Sou um homem honesto. Além disso, não tenho vontade de brigar com você, e um comerciante não é nada sem sua reputação. Mas se quiser observar e conferir, não é nenhum problema para mim.";
			link.l1 = "Sou grato, senhor. Amanhã vou cuidar do acordo e, assim que você zarpar, seguirei com meus negócios em São Cristóvão.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Capitão, eu lhe garanto: não vou decepcioná-lo, e vou cumprir todas as condições do nosso acordo.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hic! V-viva! O bom capitão finalmente pagou a gente! Três vivas pro capitão! Hic!","Tem em caneca?! Eu vou pegar uma!","Que nossas bolsas estejam cheias e nossas moças ainda mais! Viva!","E lá estavam eles, todos bons homens mortos, hic! Como o amanhecer numa espelunca de bebida. Yo ho ho e uma garrafa de rum!","Yo ho ho e uma garrafa de rum!");
			link.l1 = LinkRandPhrase("Aye, mate.","Você não acha que já tomou rum demais?","Bebida e o diabo já deram cabo do resto...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Pare! Quem está aí? Alarme! Repelem os invasores!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Har har! Você também veio atrás do tesouro do Rollie, o Capitão, hein? Procuramos, procuramos e procuramos, mas não conseguimos encontrar nada. Queria que pelo menos um desses idiotas pensasse em nadar atrás da cachoeira até aquela saliência!";
			link.l1 = "Você é um dos homens do Coronel Fox, não é?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Talvez eu tenha ligações com os Raposas do Mar. Você não precisa saber, não faz diferença. Agora não precisa saber de nada. Você encontrou meu tesouro, e por isso lhe devemos um enorme agradecimento...";
			link.l1 = "Entendi. Você não é uma Raposa do Mar, está mais para um cão... ou um chacal. O que combina mais com você?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Parece que temos um verdadeiro filósofo natural aqui, rapazes. Um grande especialista no reino animal!";
			link.l1 = "Quer testar o fio do meu sabre, chacal?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", senhor. Como posso ajudá-lo?";
			link.l1 = "Olá. Você é a Doña Belinda de Ribero?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Sim, sou eu. Com quem tenho a honra de falar?";
			link.l1 = "Capitão "+GetFullName(pchar)+", madam. Please don't be put off by my French surname; at the moment, I'm fulfilling an assignment from the Right Reverend Inquisitor of Santiago, Father Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Que interessante! Ouvi dizer que o Santo Tribunal e a Companhia de Jesus estão cheios de gente de todas as classes e nacionalidades, mas nunca tinha conhecido pessoalmente um estrangeiro trabalhando para eles até agora. Em que posso ajudá-lo, senhor?";
			link.l1 = "Você possui um objeto que interessa muito ao Reverendo Padre. Um ostensório de ouro, uma custódia que você adquiriu recentemente do banqueiro em Willemstad.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Você está muito bem informado, señor. Bem, sabendo para quem você trabalha, isso não deveria me surpreender. Sim, eu comprei o ostensório, ele certamente não deveria ter ficado largado numa loja de mercadorias ao lado de bugigangas roubadas e penhores, como se fosse uma ninharia qualquer.";
			link.l1 = "A senhora está com a custódia, madame?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Sim. Eu pretendia doá-lo à igreja da nossa paróquia, mas tanta coisa me aconteceu aqui... Eu não consegui... ah, me desculpe...";
			link.l1 = "Está chorando, madame? Minhas palavras lhe trouxeram tristeza? Se sim, por favor, me perdoe.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Ah, por favor, senhor... Vamos voltar à nossa conversa. Pelo que entendi, o padre Vincento precisa deste ostensório? Você quer que eu lhe entregue?";
			link.l1 = "Este precioso relicário era destinado à catedral de Santiago, mas foi capturado por um pirata qualquer e vendido a um agiota junto com outros objetos sagrados. Minha missão é devolver o que foi roubado ao seu devido lugar. Naturalmente, vou reembolsar totalmente suas despesas.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Oh, não faça isso! Você acha mesmo que esse dinheiro significa tanto para mim? Comprei essa custódia para a Santa Madre Igreja, e não hesitaria em entregá-la ao seu verdadeiro dono, ainda mais sendo um membro da Companhia de Jesus a serviço do Padre Vincento. Mas há outra coisa que me preocupa profundamente. Você poderia ajudar uma fiel filha da Igreja em sua necessidade?";
			link.l1 = "Você é uma dama nobre, madame. O que a aflige? Como posso ajudá-la?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Oh, mas senhor... Eu jamais ousaria pedir ajuda a um irmão jesuíta. Vocês estão sempre tão ocupados...";
			link.l1 = "Você já fez isso. Qual é o problema?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Você pode me prometer, como representante da Santa Igreja, que ninguém jamais saberá o que estou lhe pedindo?";
			link.l1 = "Dou-lhe minha palavra de honra, señora. Não é segredo de confissão, mas não direi uma só palavra sobre isso a ninguém.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Muito bem. Confio em você. Meu querido amigo Esteban Sosa se meteu em uma encrenca. Ele foi capturado por bandidos enquanto viajava e eles exigem um resgate de cem mil pesos. Não tenho todo esse dinheiro e só consegui juntar cerca de metade da quantia com a minha mesada. Não posso pedir ajuda a ninguém nessa situação, porque eles juraram que o matariam se eu fizesse isso\nAlém disso, estou muito preocupado com meu querido... amigo e temo o pior. Eles podem matá-lo assim que receberem o dinheiro, só para garantir que ele não conte nada aos guardas. Talvez você, um capitão corajoso, cristão e irmão da Sociedade, consiga convencer os bandidos a aceitarem o dinheiro que tenho e não fazerem mal a ele...";
			link.l1 = "Quando e onde vai acontecer a troca?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "O chefe deles é um homem chamado Bartie, o Açougueiro. Ele disse que vai esperar pelo resgate do Esteban todas as noites, das onze até meia-noite, na entrada da caverna, na selva...";
			link.l1 = "Essas são condições incomumente específicas...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Aparentemente, eles queriam que eu juntasse todo o resgate rapidamente e não queriam que eu pedisse ajuda a ninguém... mas eu não consigo arrumar esse dinheiro, nunca vou conseguir!";
			link.l1 = "Não chore, madame. Vou tentar ajudá-la. Um irmão da Companhia de Jesus jamais deixaria uma cristã justa em perigo.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Eu preciso confiar em você... Mas capitão, Bartie o Açougueiro também disse que, se quem trouxer o resgate não vier sozinho ou se eu procurar os guardas, ele mata o pobre Esteban na hora!";
			link.l1 = "Vou me lembrar disso.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Aqui, pegue isto. São os cinquenta mil pesos que consegui juntar. Convença esses bandidos a aceitarem pelo menos isso. Diga que não tenho mais nenhum peso! Traga Esteban de volta! Quando fizer isso, entrego de bom grado a custódia para o Padre Vincento.";
			link.l1 = "Farei tudo o que puder, senhora. Vamos torcer pelo melhor.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Que Deus te ajude, capitão corajoso! Vou rezar por você!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Tem alguma novidade, capitão?";
			link.l1 = "Ainda não. Só espere, señora. Eu não vou te decepcionar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Tem alguma novidade, capitão?";
			link.l1 = "Sim, senhora. Receio que não sejam boas notícias.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Me conte, não me faça esperar! Você encontrou os bandidos?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Aqui, pegue seus cinquenta mil de volta. Eu não precisei deles. Leve também este anel. Acho que você vai reconhecê-lo.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Aqui, pegue este anel. Acho que você vai reconhecê-lo.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "É... sim, isso me é familiar. O que aconteceu com Esteban?";
			link.l1 = "Encontrei os bandidos na caverna, como você me disse. 'Bartie, o Açougueiro' e Esteban Sosa são a mesma pessoa. Ele armou o sequestro para te extorquir. Ele me contou sobre o seu... relacionamento. Também disse que não quer mais te ver. Peguei o anel que você deu a ele como prova.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "Isto... sim, sim, eu sei. O que aconteceu com Esteban?";
			link.l1 = "Encontrei os bandidos na caverna, exatamente como você disse. Eles me atacaram, me amarraram e levaram seu dinheiro. 'Bartie o Açougueiro' e Esteban Sosa são a mesma pessoa. Ele armou o sequestro para te extorquir. Ele me contou sobre o seu... relacionamento. Esteban me deixou ir e me deu este anel como prova. Ele disse que você nunca mais vai vê-lo.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "Dios mio! Eu não acredito no que estou ouvindo! Por que tudo isso acontece comigo, por quê?! O que foi que eu fiz pra ele....";
			link.l1 = "Senhora, por favor, não se culpe por isso. Aquele canalha não vale uma única lágrima sua. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "Oh... Vou tentar me acalmar. Senhor, preciso lhe agradecer pela ajuda. Aqui, pegue seu ostensório. "+sTemp+"Vá com Deus.";
			link.l1 = "Gracias, senhora. Não se preocupe, ninguém vai descobrir o que aconteceu na caverna. Nós, jesuítas, sempre cumprimos nossa palavra. Agora, com licença, preciso ir.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Pare aí!";
			link.l1 = "Eu estou bem aqui.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Trouxe o dinheiro?";
			link.l1 = "Que pergunta mais boba. Não, estou aqui colhendo Manga Rosas... Por que mais você acha que eu teria vindo até aqui?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Oh ho ho! Um comediante! Pode entrar na caverna, Bartie está te esperando.";
			link.l1 = "Você claramente é um guarda experiente... com essa postura, estaria à altura de proteger o próprio rei Filipe. Eu mesmo vou entrar.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "Você me fez esperar... Trouxe o dinheiro com você?";
			link.l1 = "Você é o Bartie, o Açougueiro? Não parece um bandido qualquer para mim.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Por que você se importa com a minha aparência? Tem o maldito dinheiro ou não?";
			link.l1 = "Onde está o refém?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Você vai receber seu refém. Vamos, me dê a moeda. Não me irrite, garoto.";
			link.l1 = "Bartie, eu pareço um idiota pra você? Até eu ver o Esteban Sosa vivo e inteiro, você não vai receber um único peso. Onde ele está?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Ah, então você quer bancar o teimoso, é? Muito bem, vamos te dar uma boa lição... Rapazes, vamos arrebentar esse merda!";
			link.l1 = "Bastardo!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Já dançou o suficiente? Onde está Esteban Sosa? Fala logo, ou vou te afundar na água até parar de borbulhar!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "Não... Não me machuque, por favor! Eu sou Esteban Sosa.";
			link.l1 = "O quê?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Tá, tá. Eu não sou o Bartie o Açougueiro. Eu só...";
			link.l1 = "Seu canalha! Então você decidiu arrancar cem mil pesos da Dona de Ribero ao 'sequestrar' a si mesmo?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Você precisa me entender, de homem pra homem. Belinda... Ela me deixou completamente cansado com esse amor obsessivo. Não me larga um minuto, dia e noite, cara! Até o marido dela já começou a desconfiar da gente, e olha que ele mal enxerga!";
			link.l1 = "Olha só! Então, vocês são amantes?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Não mais. Acabei de fugir dela.";
			link.l1 = "E resolveu pegar umas moedas pra viagem, é? E agora, o que eu faço com você? Esconder seu corpo na selva, como tentou fazer comigo?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "Não! Eu não queria sangue, eu juro!";
			link.l1 = "É por isso que você mandou seus cães atrás de mim?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Só íamos revistar seus bolsos, só isso!";
			link.l1 = "E me deixar pelado na selva? Eu devia te amarrar e pendurar no mastro mais alto do meu navio, seu canalha! Mas não vou fazer isso, só por respeito à boa mulher que teve o azar de se envolver com você. Sabe de uma coisa? Acho que vou te levar até ela e deixar que ela decida o que fazer com você.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "Não, qualquer coisa menos isso! Eu não volto pra Cumana!";
			link.l1 = "Você prefere ficar nessa caverna para sempre?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Me poupe, senhor! Me deixe ir e eu vou zarpar daqui e nunca mais volto pra Cumana! Não vou esperar o marido da Belinda me cortar em um duelo ou mandar um assassino atrás de mim!";
			link.l1 = "Tá bom. Pelo bem da Dona de Ribero, não vou te levar até ela. Mas nem por um segundo pense que isso vai ser deixado de lado. Ela vai descobrir sobre o verme patético com quem resolveu flertar. Que sinais você tem que ela possa reconhecer?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Aqui. Este anel de turquesa aqui. Ela mesma me deu.";
			link.l1 = "Perfeito. Me dê isso e suma da minha frente!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Perfeito. E sabe, Sosa, mudei de ideia – agora sirvo à Companhia de Jesus. Como dizem as Escrituras: 'Deveis eliminar o perverso do meio de vós.' E você é um narcisista desprezível, um criminoso, e um inútil de merda. Acho que vou te afogar nesta caverna. Requiescat in pace.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "Você tem o que precisamos...";
			link.l1 = "Sério? E o que seria isso?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Eu não perguntei, riquinho. Só recebi ordens para pegar tudo o que você tem com você, absolutamente tudo. Vamos fazer isso do jeito fácil ou do jeito difícil? A escolha é sua.";
			link.l1 = "Acha que é um guerreiro, é? Você não faz ideia com quem está lidando. Eu engulo vermes como você no café da manhã.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Você é bem engraçadinho, não é, sapinho? Então vamos ver como seu sangue fica espalhado no chão!";
			link.l1 = "Vai ficar igualzinho ao seu, idiota. Deixa eu te dar uma aula de anatomia!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, tá certo, camarada... Vira os bolsos pra fora, rapidinho! Se for bonzinho e obedecer, vai sair inteiro, entendeu?";
			link.l1 = "Mas que droga, vocês de novo? Vieram até aqui também? Quem diabos contratou vocês?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "Isso não te diz respeito. Renda-se agora e viva, ou lute e nós vamos pegar seu saque do seu cadáver. Que tal esse acordo?";
			link.l1 = "Tenho uma contraproposta. Que tal eu pegar seu saque do seu cadáver?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Aguardando ordens, capitão!";
			link.l1 = "Atravessam a selva em direção ao Cabo San Antonio. Sigam pela trilha à esquerda e continuem em frente. Fiquem atentos e preparados para uma emboscada na praia. Estejam prontos. Eu vou por mar e encontro vocês lá. Quanto tempo acham que levam para chegar?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Chegaremos lá em seis horas, capitão!";
			link.l1 = "Ótimo. Vai!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "Desgraçado teimoso! Ele ainda está vivo... Eu sabia que devíamos ter usado mais pólvora! Tá bom, chega, eu mesmo acabo com você, seu filho da puta...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
